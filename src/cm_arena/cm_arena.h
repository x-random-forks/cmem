// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_arena.h                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/21 22:31:25 by rgramati          #+#    #+#             //
//   Updated: 2024/10/21 22:46:37 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CM_ARENA_H
# define CM_ARENA_H

# include <stdint.h>

# ifdef _SYS_MMAN_H
#  define CM_ARENA_MMAP		mmap
#  define CM_ARENA_MPROTECT	mprotect
#  define CM_ARENA_MUNMAP	munmap
# else
#  define CM_ARENA_MMAP		cm_mmap
#  define CM_ARENA_MPROTECT	cm_mprotect
#  define CM_ARENA_MUNMAP	cm_munmap
# endif

# define CM_ARENA_SIZE		536870912
# define CM_ARENA_CUT		4096
# define CM_ARENA_DATA_CAP	536870880

# define CM_ARENA_FB_BYTE	0x42
# define CM_ARENA_AU_BYTE	0x24

// ************************************************************************** //

struct s_cm_arena
{
	uint32_t			capacity;
	uint32_t			size;
	uint32_t			alignment;
	uint32_t			elem_size;
	char				name[16];
};

// ************************************************************************** //

#endif	// CM_ARENA_H
