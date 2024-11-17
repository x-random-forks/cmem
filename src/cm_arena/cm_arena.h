// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_arena.h                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/21 22:31:25 by rgramati          #+#    #+#             //
//   Updated: 2024/11/08 19:00:52 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CM_ARENA_H
# define CM_ARENA_H

# include <stdint.h>
# include <sys/mman.h>

# define CM_ARENA_SIZE_MIN	0x00001000
# define CM_ARENA_SIZE_MAX	0x20000000
# define CM_ARENA_DATA_CAP	0x1FFFFFE0

# define CM_ARENA_CUT_SIZE	0x00001000

# define CM_ARENA_INIT		1	

# define CM_ARENA_ZERO_BYTE 0xc0
# define CM_ARENA_FREE_BYTE	0x42
# define CM_ARENA_STOP_BYTE	0x24

// ************************************************************************** //

struct s_cm_arena
{
	uint64_t		size;
	uint64_t		page;
	uint64_t		capacity;
	struct s_flist	*free_list;
};

typedef struct s_cm_block_header
{
	uint32_t	size;
	uint32_t	usable;
	void		*dummy2;
}	t_cm_block;

// ************************************************************************** //

#endif	// CM_ARENA_H
