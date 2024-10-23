/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_chunk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:44:58 by rgramati          #+#    #+#             */
/*   Updated: 2024/09/23 20:23:11 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

t_cm_chunk	*cm_chunk_init(const char *name, uint32_t elem_size)
{
	struct s_cm_chunk	*chunk;
	uint32_t			offset;

	chunk = malloc(sizeof(struct s_cm_chunk));
	if (chunk && name)
	{
		cm_memset(chunk, 0, sizeof(struct s_cm_chunk));
		offset = cm_twos_power_raise(elem_size);
		chunk->capacity = CM_CHUNK_DATA_CAP / offset;
		chunk->alignment = offset;
		chunk->elem_size = elem_size + !elem_size;
		cm_memcpy(chunk->name, (void *)name, cm_min(cm_strlen(name), 15));
		if (!chunk->alignment || !chunk->capacity)
		{
			free(chunk);
			chunk = NULL;
		}
	}
	return (chunk);
}

void	cm_chunk_clear(t_cm_chunk *chunk_ptr, uint32_t flags)
{
	struct s_cm_chunk	*chunk;
	uint32_t			param;
	void				*ptr;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	if (chunk->next)
		cm_chunk_clear(chunk->next, flags);
	param = flags & 0xFF;
	flags &= ~(0xFF);
	if (!chunk)
		return ;
	if (flags & CM_CLEAR_WIPE)
	{
		chunk->size -= param;
		ptr = cm_chunk_at(chunk, chunk->size - 1);
		cm_memset(ptr, 0, param * chunk->alignment);
	}
	if (flags & CM_CLEAR_NULL)
		cm_memset(chunk, 0, 32);
	if ((flags & CM_CLEAR_FREE) == CM_CLEAR_FREE)
		free(chunk);
}

void	*cm_chunk_alloc(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;
	void				*ptr;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	ptr = NULL;
	if (chunk)
	{
		if (chunk->size >= chunk->capacity)
			return (ptr);
		ptr = cm_chunk_at(chunk, chunk->size);
		if (!chunk->size)
			chunk->iterator.start = ptr;
		chunk->iterator.end = ptr;
		chunk->size++;
	}
	return (ptr);
}

void	*cm_chunk_push(t_cm_chunk *chunk_ptr, void *elem, uint32_t elem_size)
{
	struct s_cm_chunk	*chunk;
	void				*ptr;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	ptr = NULL;
	if (chunk && elem)
	{
		if (elem_size != chunk->elem_size)
			return (ptr);
		ptr = cm_chunk_alloc(chunk);
		if (!ptr)
			return (ptr);
		cm_memcpy(ptr, elem, elem_size);
	}
	return (ptr);
}

void	*cm_chunk_pop(t_cm_chunk *chunk_ptr, void *elem)
{
	struct s_cm_chunk	*chunk;
	void				*ptr;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	ptr = NULL;
	if (chunk && elem)
	{
		if (chunk->size == 0)
			return (ptr);
		chunk->size--;
		ptr = cm_chunk_at(chunk, chunk->size);
		cm_memcpy(elem, ptr, chunk->elem_size);
	}
	return (elem);
}
