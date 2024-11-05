// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cmem.h                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 00:35:57 by rgramati          #+#    #+#             //
//   Updated: 2024/11/01 15:57:54 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CMEM_H
# define CMEM_H

# include <stdint.h>

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
#  ifndef CM_LIMG_IMPLEMENTATION
#   define CM_LIMG_IMPLEMENTATION
#  endif
# endif

# ifdef CM_CHUNK_IMPLEMENTATION
#  include <../src/cm_chunk/cm_chunk.h>
# endif

# define CM_BIT_COUNT	"\
\x00\x00\x01\x00\x02\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\
\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

/**
 * @enum	e_chunk_flags
 *
 * 	CM_CLEAR_ZERO : clear structure data space.
 *	CM_CLEAR_NULL : reset structure settings.
 *	CM_CLEAR_FREE : frees the structure.
 *					is also CM_CLEAR_ZERO | CM_CLEAR_NULL
 *	CM_CLEAR_WIPE : erase values from the strucutre.
 *					can be ORed with a number of values to
 *					erase multiple values.
 */
enum	e_clear_flags
{
	CM_CLEAR_ZERO = 1 << 8,
	CM_CLEAR_NULL = 1 << 9,
	CM_CLEAR_WIPE = 1 << 10,
	CM_CLEAR_FREE = CM_CLEAR_ZERO | CM_CLEAR_NULL | 1 << 11
};

// ************************************************************************** //
# ifdef CM_CHUNK_IMPLEMENTATION

typedef void				t_cm_chunk;
typedef struct s_cm_iter	t_cm_iterator;

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
cm_chunk_clear(t_cm_chunk *chunk_ptr, uint32_t flags);

/**
 * @brief	Allocate space on a memory chunk for a new element.
 *
 * @param		(chunk)		Chunk pointer.
 *
 * @returns	A pointer to the allocated space.
 */
void
*cm_chunk_alloc(t_cm_chunk *chunk_ptr);

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
*cm_chunk_push(t_cm_chunk *chunk_ptr, void *elem, uint32_t elem_size);

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
*cm_chunk_pop(t_cm_chunk *chunk_ptr, void *elem);

/**
 * @brief	Get the element at a certain index on a memory chunk.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(index)		The index.
 *
 * @returns	A pointer to this element (depending on chunk alignment);
 */
void
*cm_chunk_at(t_cm_chunk *chunk_ptr, uint32_t index);

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
cm_chunk_index(t_cm_chunk *chunk_ptr, void *elem);

/**
 * @brief	Get chunk size.
 *
 * @param		(chunk)		Chunk pointer.
 * 
 * @returns	Chunk actual size.
 */
uint32_t
cm_chunk_size(t_cm_chunk *chunk_ptr);

/**
 * @brief	Get the next element from iteration.
 *
 * @param		(chunk)		Chunk pointer.
 *
 * @returns	An opaque pointer to the element.
 * @note	This used with a NULL current iterator set it to start iterator.
 */
void
*cm_chunk_it_next(t_cm_chunk *chunk_ptr);

/**
 * @brief	Get the start iterator from a chunk.
 *
 * @param		(chunk)		Chunk pointer.
 *
 * @returns	An opaque pointer to the start iterator.
 */
void
*cm_chunk_it_start(t_cm_chunk *chunk_ptr);

/**
 * @brief	Get the end iterator from a chunk.
 *
 * @param		(chunk)		Chunk pointer.
 *
 * @returns	An opaque pointer to the end iterator.
 */
void
*cm_chunk_it_end(t_cm_chunk *chunk_ptr);

/**
 * @brief	Returns the next chunk pointer.
 *
 * @param		(chunk)		Chunk pointer.
 *
 * @return	Next chunk pointer, NULL if no linking
 */
t_cm_chunk	*cm_chunk_next(t_cm_chunk *chunk_ptr);

/**
 * @brief	Allocates new linked chunk for additional space.
 *
 * @param		(chunk)		Chunk pointer.
 */
void	cm_chunk_link(t_cm_chunk *chunk_ptr);

# endif	//	CM_CHUNK_IMPLEMENTATION

// ************************************************************************** //

#ifdef CM_ARENA_IMPLEMENTATION

# include <../src/cm_arena/cm_arena.h>
typedef void				t_cm_arena;

#endif

// ************************************************************************** //

#ifdef CM_HTABLE_IMPLEMENTATION

# include <../src/cm_htable/cm_htable.h>
typedef void				t_cm_htable;

t_cm_htable
*cm_htable_init(uint32_t capacity);

void
cm_htable_clear(t_cm_htable *htable_ptr, uint32_t flags);

void
cm_htable_set(t_cm_htable *htable_ptr, const char *key, void *data);

void
*cm_htable_get(t_cm_htable *htable_ptr, const char *key);

void
*cm_htable_remove(t_cm_htable *htable_ptr, const char *key);

#endif

// ************************************************************************** //

#ifdef CM_LIMG_IMPLEMENTATION

# include <../src/cm_limg/cm_limg.h>

typedef enum e_open_types
{
	CM_OPEN_LOAD = 1,
	CM_OPEN_SAVE = 1 << 1,
	CM_OPEN_ALLOC = 1 << 2
}	t_open_types;

uint32_t
cm_bmp(const char *filename, uint32_t **data_ptr, uint64_t flags);

// TODO : #include <zlib.h> and png parsing :)

#endif

// ************************************************************************** //

uint32_t
cm_twos_power_raise(uint32_t x);

uint32_t
cm_min(uint32_t a, uint32_t b);

uint32_t
cm_strlen(const char *str);

int32_t
cm_strcmp(const char *s1, const char *s2);

char
*cm_strdup(const char *str);

void
cm_memset(void *ptr, unsigned char c, uint32_t n);

void
cm_memcpy(void *dst, void *src, uint32_t n);

void
cm_memmove(void *dst, void *src, uint32_t n);

/* ************************************************************************** */

#endif
