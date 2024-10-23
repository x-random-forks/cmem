/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:32:49 by rgramati          #+#    #+#             */
/*   Updated: 2024/09/23 20:28:57 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmem.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t	cm_min(uint32_t a, uint32_t b)
{
	if (a < b)
		return (a);
	return (b);
}

uint32_t	cm_twos_power_raise(uint32_t x)
{
	x += !x;
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return (x);
}

uint32_t	cm_strlen(const char *str)
{
	const char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

int32_t	cm_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*cm_strdup(const char *str)
{
	char		*cpy;
	uint32_t	len;

	len = cm_strlen(str);
	cpy = malloc(len + 1);
	if (cpy)
		cm_memcpy(cpy, (void *)str, len);
	cpy[len] = 0;
	return (cpy);
}

void	cm_memset(void *ptr, unsigned char c, uint32_t n)
{
	while (n && (uintptr_t)ptr & (sizeof(uint64_t) - 1))
	{
		*(uint8_t *)ptr = c;
		ptr++;
		n--;
	}
	while (n >= sizeof(uint64_t))
	{
		*(uint64_t *)ptr = c * (-1UL / 255);
		ptr += sizeof(uint64_t);
		n -= sizeof(uint64_t);
	}
	while (n)
	{
		*(uint8_t *)ptr = c;
		ptr++;
		n--;
	}
}

void	cm_memcpy(void *dst, void *src, uint32_t n)
{
	while (n && (uintptr_t)src & (sizeof(uint64_t) - 1))
	{
		*(uint8_t *)dst = *(uint8_t *)src;
		n--;
		src++;
		dst++;
	}
	while (n >= sizeof(uint64_t))
	{
		*(uint64_t *)dst = *(uint64_t *)src;
		n -= sizeof(uint64_t);
		src += sizeof(uint64_t);
		dst += sizeof(uint64_t);
	}
	while (n)
	{
		*(uint8_t *)dst = *(uint8_t *)src;
		n--;
		src++;
		dst++;
	}
}
