// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_links.c                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/08 18:03:50 by rgramati          #+#    #+#             //
//   Updated: 2024/10/22 22:46:02 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdint.h>
#include <unistd.h>

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

t_cm_chunk	*cm_chunk_next(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	return (chunk->next);
}

void	cm_chunk_link(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	chunk->next = cm_chunk_init(chunk->name, chunk->alignment);
}

uint32_t	cm_chunk_size(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	return (chunk->size);
}
