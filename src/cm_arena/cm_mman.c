// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_mman.c                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/21 22:46:55 by rgramati          #+#    #+#             //
//   Updated: 2024/10/21 23:40:17 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <unistd.h>
#include <stdint.h>

#ifndef CM_ARENA_IMPLEMENTATION
# define CM_ARENA_IMPLEMENTATION
#endif
#include <cmem.h>

#ifdef _SYS_MMAN_H

t_cm_arena	*cm_arena_init()
{
	struct s_cm_arena	*arena;

	arena = 	
}

#else

t_cm_arena	*cm_arena_init()
{
	struct s_cm_arena	*arena;

	arena = 
}

#endif

void	cm_arena_clear()
{

}
