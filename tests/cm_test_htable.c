// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_test_htable.c                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/07 00:46:52 by rgramati          #+#    #+#             //
//   Updated: 2024/10/07 01:07:27 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <assert.h>
#include <stdint.h>

#include <cmemtest.h>

#ifndef CM_HTABLE_IMPLEMENTATION
# define CM_HTABLE_IMPLEMENTATION
#endif
#include <cmem.h>

#include <stdio.h>
void	cm_unit_test_htable(void)
{
	struct s_cm_htable	*ptr;

	ptr = cm_htable_init(45);
	(void)ptr;

	cm_htable_set(ptr, "Mateo", (void *)&"Le portugais");
	cm_htable_set(ptr, "Killian", (void *)&"L'autiste");

	printf("%s\n", (char *)cm_htable_get(ptr, "Mateo"));
}
