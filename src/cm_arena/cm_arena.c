// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_arena.c                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/11/07 18:50:22 by rgramati          #+#    #+#             //
//   Updated: 2024/11/08 19:07:10 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "cm_arena.h"
#include <stdint.h>
#include <stdio.h>

#ifndef CM_ARENA_IMPLEMENTATION
# define CM_ARENA_IMPLEMENTATION
#endif
#include <cmem.h>



void	cm_arena_display(t_cm_arena *arena_ptr)
{
	struct s_cm_arena	*arena;
	uint32_t			remain;
	const char			*colors[4] = {"\033[38;2;222;207;172m", "\033[38;2;197;176;138m", "\033[38;2;166;140;95m", "\033[38;2;106;96;76m"};

	printf("--------------------------------------------------------------------\n");
	arena = (struct s_cm_arena *)arena_ptr;
	remain = sizeof(struct s_cm_arena);
	for (uint32_t i = 0; i < sizeof(struct s_cm_arena); i += 8)
	{
		if (!(i % 16))
			printf("\033[1m %16p  ", arena);
		printf("%s", colors[i / 8]);
		for (uint32_t j = 0; j < 8; ++j)
		{
			printf("%s%02x ", j & 7 ? "" : " " ,*((uint8_t *)arena + i + j));
		}
		if ((i % 16) == 8)
			printf("\n\033[0m");
	}
	printf("\n\033[0m");
	while (remain < arena->page)
	{
		printf("[%16p] ", ((uint8_t *)arena) + remain);
		for (uint32_t i = 0; i < 16; ++i)
		{
			printf("%s%02x ", i & 7 ? "" : " " ,*((uint8_t *)arena + remain + i));
		}
		printf("\n");
		remain += 16;
	}
	printf("--------------------------------------------------------------------\n");
}

void	cm_arena_cut_init(t_cm_arena *arena_ptr, uint32_t amount, uint8_t init)
{
	struct s_cm_arena	*arena;
	uint64_t			page_size;
	uint64_t			new;

	arena = (struct s_cm_arena *)arena_ptr;
	page_size = CM_ARENA_CUT_SIZE;
	new = (uintptr_t)(arena);
	if (!init)
		new += arena->page;
	mprotect((void *)new, page_size, PROT_READ | PROT_WRITE);
	cm_memset((void *)(new + sizeof(struct s_cm_arena)), CM_ARENA_ZERO_BYTE, page_size * amount - sizeof(struct s_cm_arena));
	arena->page = arena->page + (page_size * amount);
}

t_cm_arena	*cm_arena_init()
{
	struct s_cm_arena	*arena;
	void				*data;

	data = mmap(NULL, CM_ARENA_SIZE_MAX, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	arena = (struct s_cm_arena *)data;
	if (arena)
	{
		cm_arena_cut_init(arena, 1, CM_ARENA_INIT);
		arena->capacity = CM_ARENA_DATA_CAP;
		arena->size = sizeof(struct s_cm_arena);
		if (!arena->capacity)
		{
			munmap(data, CM_ARENA_SIZE_MAX);
			arena = NULL;
		}
	}
	return (arena);
}

void	cm_arena_clear(t_cm_arena *arena_ptr, uint32_t flags)
{
	struct s_cm_arena	*arena;
	uint32_t			size;

	arena = (struct s_cm_arena *)arena_ptr;
	if (arena)
	{
		if (flags & CM_CLEAR_NULL)
			cm_memset(arena, 0, sizeof(struct s_cm_arena));
		if (flags & CM_CLEAR_ZERO)
		{
			size = arena->page;
			if (size)
				size -= sizeof(struct s_cm_arena);
			cm_memset(arena + sizeof(struct s_cm_arena), 0, size);
			size = arena->page;
			if (size)
				size -= CM_ARENA_CUT_SIZE;
			mprotect(arena + CM_ARENA_CUT_SIZE, size, PROT_NONE);
		}
		if (flags & CM_CLEAR_FREE)
			munmap(arena, arena->page);
	}
}

void	*cm_arena_alloc(t_cm_arena *arena_ptr, uint64_t size)
{
	struct s_cm_arena	*arena;
	t_cm_block			*head;
	uint32_t			offset;
	void				*ptr;

	arena = (struct s_cm_arena *)arena_ptr;
	ptr = NULL;
	if (arena && size && !(size >> 24))
	{	
		head = (t_cm_block *)((uintptr_t)arena + arena->size);
		offset = 32 - ((32 + size) & 31);
		head->size = size + offset;
		head->usable = size;
		ptr = (void *)((uintptr_t)head + sizeof(t_cm_block));
		cm_memset(ptr + head->usable, CM_ARENA_ZERO_BYTE, offset);
		cm_memset(ptr, 0, head->usable);
		arena->size += sizeof(t_cm_block) + head->size;
	}
	return (ptr);
}

void	cm_arena_free(t_cm_arena *arena_ptr, void *ptr)
{
	struct s_cm_arena	*arena;
	t_cm_block			*block;

	arena = (struct s_cm_arena *)arena_ptr;
	if (arena)
	{
		if ((uintptr_t)ptr - (uintptr_t)arena >= arena->page)
			return ;
		block = (t_cm_block *)((uintptr_t)ptr - sizeof(t_cm_block));
		((struct s_flist *)ptr)->next = arena->free_list;
		arena->free_list = ptr;
		arena->size -= block->size + sizeof(t_cm_block);
	}
}

