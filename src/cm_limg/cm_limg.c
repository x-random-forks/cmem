// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_limg.c                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/13 02:46:41 by rgramati          #+#    #+#             //
//   Updated: 2024/10/13 03:25:18 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef CM_LIMG_IMPLEMENTATION
# define CM_LIMG_IMPLEMENTATION
#endif
#include <cmem.h>

#define CM_BMP_SIGNATURE	0x4d42

int32_t	cm_bmp_header(void *bmp, t_bmp_header *header)
{
	cm_memcpy((uint8_t *)&(header->signature[1]), bmp, 14);
	if (header->signature[1] != CM_BMP_SIGNATURE)
		return (1);
	if (header->file_size == 0)
		return (1);
	if (header->data_offset != 54)
		return (1);
	return (0);
}

int32_t cm_bmp_info(void *bmp, t_bmp_info *info)
{
	cm_memcpy(info, bmp, 40);
	if (info->size != 40)
		return (1);
	if (info->bpp != 1 && info->bpp != 4 && info->bpp != 8 \
		&& info->bpp != 16 && info->bpp != 24)
		return (1);
	if (info->compression > 2)
		return (1);
	return (0);
}

int32_t	cm_file_open(const char *filename)
{
	int32_t	fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

uint32_t	cm_bmp_fill(int32_t fd, uint32_t **data_ptr, t_bmp_header *h, t_bmp_info *i)
{
	uint32_t	size;
	uint8_t		pixel[3];
	uint32_t	bytes;
	uint32_t	*cursor;

	if (!data_ptr)
		return (1);
	size = h->file_size - h->data_offset;
	if (i->bpp != 24)
	{
		printf("TODO : implement other types of colors");
		return (1);
	}
	cursor = *data_ptr;
	while (size)
	{
		bytes = read(fd, pixel, 3);
		if (bytes < 0)
			return (1);
		size -= bytes;
		*cursor++ = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16);
	}
	return (0);
}

uint32_t	cm_bmp(const char *filename, uint32_t **data_ptr)
{
	int32_t			fd;
	char			buffer[64];
	t_bmp_header	header;
	t_bmp_info		info;

	fd = cm_file_open(filename);
	if (fd == -1 || !data_ptr)
		return (1);
	cm_memset(buffer, 0, 256);
	if (read(fd, buffer, 14) != 14)
		return (1);
	if (cm_bmp_header(buffer, &header))
		return (1);
	if (read(fd, buffer, 40) != 40)
		return (1);
	if (cm_bmp_info(buffer, &info) || info.bpp <= 8) // TODO : Handle palette parsing
		return (1);
	*data_ptr = malloc(header.file_size - header.data_offset);
	if (!*data_ptr)
		return (1);
	if (cm_bmp_fill(fd, data_ptr, &header, &info))
		return (1);
	return (0);
}
