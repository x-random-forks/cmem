// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_limg.h                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/13 02:41:27 by rgramati          #+#    #+#             //
//   Updated: 2024/10/13 03:36:08 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CM_LIMG_H
# define CM_LIMG_H

# include <stdint.h>

/* ************************************************************************** */

typedef struct s_bmp_header
{
	union
	{
		uint32_t	sign_byte;
		uint16_t	signature[2];
	};
	uint32_t	file_size;
	uint32_t	reserved;
	uint32_t	data_offset;
}	t_bmp_header;

typedef struct s_bmp_info
{
	uint32_t	size;
	uint32_t	width;
	uint32_t	height;
	uint16_t	planes;
	uint16_t	bpp;
	uint32_t	compression;
	uint32_t	imgsize;
	uint32_t	hres;
	uint32_t	vres;
	uint32_t	colors;
	uint32_t	important;
}	t_bmp_info;

/* ************************************************************************** */

#endif
