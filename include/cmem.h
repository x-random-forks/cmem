// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cmem.h                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 00:35:57 by rgramati          #+#    #+#             //
//   Updated: 2024/10/06 03:10:04 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CMEM_H
# define CMEM_H

# include <stdint.h>

# include <../src/cm_chunk/cm_chunk.h>
typedef void				t_cm_chunk;
typedef struct s_cm_iter	t_cm_iterator;

# include <../src/cm_arena/cm_arena.h>
typedef void				t_cm_arena;

# include <../src/cm_htable/cm_htable.h>
typedef void				t_cm_htable;

# define CM_INCLUDE_ALL

# ifdef CM_INCLUDE_ALL
#  ifndef CM_CHUNK_IMPLEMENTATION
#   define CM_CHUNK_IMPLEMENTATION
#  endif
#  ifndef CM_ARENA_IMPLEMENTATION
#   define CM_ARENA_IMPLEMENTATION
#  endif
#  ifndef CM_HTABLE_IMPLEMENTATION
#   define CM_HTABLE_IMPLEMENTATION
#  endif
# endif

// ************************************************************************** //
# ifdef CM_CHUNK_IMPLEMENTATION

/**
 * @brief	Init a memory chunk.
 *
 * @param		(name)		A name for the memory chunk (15 chars max).
 * @param		(elem_size)	Element size, pass sizeof(elem) to setup correctly.
 *
 * @returns	A pointer to a memory chunk.
 */
t_cm_chunk
*cm_chunk_init(const char *name, uint32_t elem_size);

/**
 * @brief	Perform clear operations on a memory chunk.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(flags)		Combination of e_chunk_flags.
 */
void
cm_chunk_clear(t_cm_chunk *chunk, uint32_t flags);

/**
 * @brief	Allocate space on a memory chunk for a new element.
 *
 * @param		(chunk)		Chunk pointer.
 *
 * @returns	A pointer to the allocated space.
 */
void
*cm_chunk_alloc(t_cm_chunk *chunk);

/**
 * @brief	Pushes an element on a memory chunk.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(elem)		Opaque pointer to source data.
 * @param		(elem_size)	Element size of source.
 *
 * @note	A safe way to use this is by passing both the adress and the size
 *			of a static object.
 *			cm_chunk_push(example_chunk, &object, sizeof(object));
 *
 * @returns A pointer to the pushed element.
 */
void
*cm_chunk_push(t_cm_chunk *chunk, void *elem, uint32_t elem_size);

/**
 * @brief	Pops an element from a memory chunk.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(elem)		Opaque pointer to store the popped data.
 *							Can be NULL if you dont need to save this.
 *
 * @returns	Destination pointer, so elem.
 */
void
*cm_chunk_pop(t_cm_chunk *chunk, void *elem);

/**
 * @brief	Get the element at a certain index on a memory chunk.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(index)		The index.
 *
 * @returns	A pointer to this element (depending on chunk alignment);
 */
void
*cm_chunk_at(t_cm_chunk *chunk, uint32_t index);

/**
 * @brief	Get an element index from its address.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(elem)		The element.
 *
 * @returns	The index of elem in the chunk.
 * @note	Will return ((uint32_t)-1) if the adress is not aligned with
 *			chunk settings nor in this chunk.
 */
uint32_t
cm_chunk_index(t_cm_chunk *chunk, void *elem);

/**
 * @brief	Get the next element from iteration.
 *
 * @param		(chun)		Chunk pointer.
 *
 * @returns	An opaque pointer to the element.
 * @note	This used with a NULL current iterator set it to start iterator.
 */
void
*cm_chunk_it_next(t_cm_chunk *chunk);

/**
 * @brief	Get the start iterator from a chunk.
 *
 * @param		(chun)		Chunk pointer.
 *
 * @returns	An opaque pointer to the start iterator.
 */
void
*cm_chunk_it_start(t_cm_chunk *chunk);

/**
 * @brief	Get the end iterator from a chunk.
 *
 * @param		(chun)		Chunk pointer.
 *
 * @returns	An opaque pointer to the end iterator.
 */
void
*cm_chunk_it_end(t_cm_chunk *chunk);

# endif	//	CM_CHUNK_IMPLEMENTATION

/* * UTILS ****************************************************************** */

uint32_t
cm_twos_power_raise(uint32_t x);

uint32_t
cm_min(uint32_t a, uint32_t b);

uint32_t
cm_strlen(const char *str);

void
cm_memset(void *ptr, unsigned char c, uint32_t n);

void
cm_memcpy(void *dst, void *src, uint32_t n);

/* ************************************************************************** */

#endif
