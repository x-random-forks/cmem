// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   libcmem_test.c                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 01:49:32 by rgramati          #+#    #+#             //
//   Updated: 2024/10/07 00:53:38 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdint.h>
#include <stdio.h>

#include <cmemtest.h>

#define CM_INCLUDE_ALL
#include <cmem.h>

void	cm_unit_test_chunk(void);
void	cm_unit_test_arena(void);
void	cm_unit_test_htable(void);

int32_t	cm_strcmp(const char *s1, const char *s2);

void	cm_launch_tester(char **argv)
{
	UNUSED(argv);
	PRINTF(
		CM_ANSI_CLEAR CM_ANSI_BOLD CM_LINE CM_COLOR_SUBTI
		" - LibCMem - testing suite\n"
		CM_ANSI_RESET CM_ANSI_BOLD CM_LINE CM_ANSI_RESET
	);
	// TODO: NON canonical mode application
	cm_unit_test_chunk();
	cm_unit_test_htable();
}

int	main(int argc, char **argv)
{
	if (argc != 1)
	{
		PRINTF(
			CM_ANSI_BOLD CM_LINE CM_COLOR_WRONG
			"[cmem test]"
			CM_ANSI_RESET CM_ANSI_BOLD
			": Usage: ./libcmem_test\n"
			CM_LINE CM_ANSI_RESET
		);
		return (1);
	}
	cm_launch_tester(argv);
	return (0);
}
