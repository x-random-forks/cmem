// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cmemtest.h                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/07 00:19:29 by rgramati          #+#    #+#             //
//   Updated: 2024/10/29 01:12:31 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CMEMTEST_H
# define CMEMTEST_H

# define UNUSED(X)			(void)(X)
# define UNIMPLEMENTED(X)	{printf("Unimplemented: %s\n", X); exit(42);}

# define CM_ANSI_BOLD		"\033[1m"
# define CM_ANSI_RESET		"\033[0m"
# define CM_ANSI_CLEAR		"\033c"

# define CM_COLOR_TEXT		"\033[38;2;198;197;180;1m"
# define CM_COLOR_TITLE		"\033[38;2;33;50;75;1m"
# define CM_COLOR_SUBTI		"\033[38;2;120;185;186;1m"
# define CM_COLOR_WRONG		"\033[38;2;206;71;47;1m"
# define CM_COLOR_PASSED	"\033[38;2;8;71;26;1m"

# if defined (_STDIO_H)
#  define PRINTF printf
# else
#  define PRINTF ft_printf
# endif

# define CM_LINE	"\
--------------------------------------------------------\
--------------------------------------------------------\
--------------------------------------------------------\
--------------------------------------------\n"

#endif
