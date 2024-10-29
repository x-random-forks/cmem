// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_limg.c                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/13 02:46:41 by rgramati          #+#    #+#             //
//   Updated: 2024/10/29 00:01:25 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "cm_limg.h"
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	if (header->data_offset != 54 && header->data_offset != 1078)
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
	if (fd == -1)
	{
		printf("Errno %d : %s\n", errno, strerror(errno));
	}
	return (fd);
}

uint32_t	cm_bmp_fill_bpp24(int32_t fd, uint32_t **data_ptr, t_bmp_info *i, uint32_t size)
{
	uint32_t	*cursor;
	uint32_t	coords[2];
	uint8_t		pixel[3];
	uint32_t	bytes;
	uint32_t	padding;

	cursor = *data_ptr;
	coords[0] = 0;
	padding = (i->width * 3) & 3;
	while (coords[0] < i->height)
	{
		coords[1] = 0;
		while (coords[1] < i->width)
		{
			bytes = read(fd, &pixel, 3);
			if (bytes <= 0)
				break ;
			size -= bytes;
			cursor[(i->height - coords[0] - 1) * i->width + coords[1]] = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16);
			coords[1]++;
		}
		read(fd, &pixel, padding);
		coords[0]++;
	}
	return (!!size);
}

uint32_t	cm_bmp_fill_bpp8(int32_t fd, uint32_t **data_ptr, t_bmp_info *i, uint32_t size)
{
	uint32_t	*cursor;
	uint32_t	buffer[256];
	uint8_t		pixel;
	uint32_t	coords[2];
	uint32_t	bytes;

	bytes = read(fd, (char *)&buffer, 1024);
	if (bytes != 1024)
		return (1);
	cursor = *data_ptr;
	coords[0] = 0;
	while (coords[0] < i->height)
	{
		coords[1] = 0;
		while (coords[1] < i->width)
		{
			bytes = read(fd, &pixel, 1);
			if (bytes <= 0)
				break ;
			size -= bytes;
			uint32_t index = (i->height - coords[0] - 1) * i->width + coords[1];
			cursor[index] = buffer[(unsigned char)pixel];
			coords[1]++;
		}
		coords[0]++;
	}
	return (!!size);
}

uint32_t	cm_bmp_fill(int32_t fd, uint32_t **data_ptr, t_bmp_header *h, t_bmp_info *i)
{
	uint32_t	bmp_size;

	bmp_size = (h->file_size - h->data_offset); 
	if (i->bpp != 24 && i->bpp != 8)
	{
		printf("TODO : implement other types of colors");
		return (1);
	}
	if (i->bpp == 24)
		cm_bmp_fill_bpp24(fd, data_ptr, i, bmp_size);
	else if (i->bpp == 8)
		cm_bmp_fill_bpp8(fd, data_ptr, i, bmp_size);
	return (0);
}

void	cm_bmp_save(const char *filename, uint32_t *source, uint32_t width, uint32_t height)
{
	t_bmp_header	header = {0};
	t_bmp_info		info = {0};
	uint32_t		invheight;

	header.signature[1] = 0x4d42;
	header.reserved = 0;
	header.data_offset = 54;
	info.planes = 1;
	info.bpp = 24;
	info.size = 40;
	info.width = width;
	info.height = height;
	uint32_t	padding = (width * 3) & 3;
	info.imgsize = width * height * 3 + height * padding;
	uint8_t	*image = malloc(info.imgsize);
	uint32_t	img_index = 0;


	for (uint32_t i = 0; i < height; i++)
	{
		invheight = (height - i - 1);
		uint32_t	j;
		for (j = 0; j < width; j++)
		{
			image[img_index++ + 2] = source[invheight * width + j] & 0xFF;
			image[img_index++] = (source[invheight * width + j] >> 8) & 0xFF;
			image[img_index++ - 2] = ((source[invheight * width + j] >> 16) & 0xFF);
		}
		for (uint32_t k = 0; k < padding; ++k)
			image[img_index++] = 0;
	}
	header.file_size = header.data_offset + info.imgsize;
	int fd = open(filename, O_WRONLY | O_CREAT, 0644);
	write(fd, (uint8_t *)&header.signature[1], 14);
	write(fd, (uint8_t *)&info, 40);
	write(fd, image, info.imgsize);
	close(fd);
}

uint32_t	cm_bmp_load(const char *filename, uint32_t **data_ptr, uint16_t *w, uint16_t *h)
{
	int32_t			fd;
	char			buffer[64];
	t_bmp_header	header;
	t_bmp_info		info;

	fd = cm_file_open(filename);
	if (fd == -1 || !data_ptr)
		return (1);
	cm_memset(buffer, 0, 64);
	if (read(fd, &buffer, 14) != 14)
		return (1);
	if (cm_bmp_header(buffer, &header))
		return (1);
	if (read(fd, &buffer, 40) != 40)
		return (1);
	if (cm_bmp_info(buffer, &info) || info.bpp < 8) // TODO : Handle palette parsing
		return (1);
	if (info.bpp == 24)
		*data_ptr = malloc(((header.file_size - header.data_offset) << 2) / 3);
	else if (info.bpp == 8)
		*data_ptr = malloc(((header.file_size - header.data_offset) << 2));
	if (!*data_ptr)
		return (1);
	if (cm_bmp_fill(fd, data_ptr, &header, &info))
		return (1);
	*w = info.width;
	*h = info.height;
	return (0);
}

uint32_t	cm_bmp(const char *filename, uint32_t **data_ptr, uint64_t flags)
{
	uint16_t	width;
	uint16_t	height;

	width = (flags & 0xFFFF0000) >> 16; 
	height = (flags & 0xFFFF00000000) >> 32;
	flags &= 0xFFFF;
	if (flags & CM_OPEN_LOAD)
		cm_bmp_load(filename, data_ptr, &width, &height);
	if (flags & CM_OPEN_SAVE)
		cm_bmp_save(filename, *data_ptr, width, height);
	return ((uint32_t)width << 16 | height);
}
