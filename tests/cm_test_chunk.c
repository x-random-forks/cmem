// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_test_chunk.c                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 21:58:01 by rgramati          #+#    #+#             //
//   Updated: 2024/10/07 00:35:31 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include <cmemtest.h>

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

void	cm_test_result(uint32_t res, const char *test)
{
	if (!res)
	{
		PRINTF(
			CM_ANSI_BOLD CM_COLOR_PASSED
			"    [ Test passed ! ] > "
			CM_COLOR_TEXT
			"%s\n"
			CM_ANSI_RESET,
			test
		);
		return ;
	}
	PRINTF(
		CM_ANSI_BOLD CM_COLOR_WRONG
		"    [ Test FAILED ! ] > "
		CM_COLOR_TEXT
		"%s\n"
		CM_ANSI_RESET,
		test
	);
	exit(42);
}

uint32_t	assert_chunk_settings(
	struct s_cm_chunk	*chunk,
	uint32_t size,
	uint32_t elem_size,
	uint32_t capacity,
	uint32_t alignment
)	{
	return (
		chunk->size			!= size			||
		chunk->elem_size	!= elem_size	||
		chunk->capacity		!= capacity		||
		chunk->alignment	!= alignment
	);
}

void	cm_unit_test_chunk(void)
{
	struct s_cm_chunk	*ptr;

	PRINTF(
		CM_ANSI_BOLD CM_COLOR_TITLE
		" [Data chunks]\n"
		CM_ANSI_RESET
	);
	ptr = cm_chunk_init("dummy", 32);
	cm_test_result(
		assert_chunk_settings(ptr, 0, 32, sizeof(ptr->data) / 32, 32),
		"cm_chunk_init()"
	);
	cm_chunk_clear(ptr, CM_CLEAR_NULL);
	cm_test_result(
		assert_chunk_settings(ptr, 0, 0, 0, 0),
		"cm_chunk_clear() with CM_CLEAR_NULL"
	);
}
