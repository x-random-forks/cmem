// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   libcmem_test.c                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 01:49:32 by rgramati          #+#    #+#             //
//   Updated: 2024/10/06 01:52:11 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdio.h>
#define CM_INCLUDE_ALL
#include <cmem.h>

int	main(void)
{
	t_cm_chunk	*test;

	test = cm_chunk_init("hello", 6);

	void	*tmp;
	for (int i = 0; i < 13; i++)
		tmp = cm_chunk_alloc(test);

	uint32_t	ind = cm_chunk_index(test, tmp);
	printf("index is %d\n", ind);

	return (0);
}
