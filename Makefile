# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 17:09:56 by rgramati          #+#    #+#              #
#    Updated: 2024/10/06 01:54:19 by rgramati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#
# Vars
#

LIBNAME		=	libcmem

SRC_DIR		:=	src

OBJS_DIR	:=	build

SRCS		:=	cm_chunk/cm_chunk.c		\
				cm_chunk/cm_access.c	\
				utils.c
				# cm_arena/cm_arena.c		\
				# cm_htable/cm_htable.c	\

SRCS		:=	$(addprefix $(SRC_DIR)/, $(SRCS))

OBJS 		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))
SOBJS 		:=	$(addprefix $(OBJS_DIR)/PIC/, $(SRCS:%.c=%.o))

INCLUDES	:=	include

CC			:=	gcc

CFLAGS		:=	-Wall -Wextra -Werror -g3

COPTS		:=	-I ./$(INCLUDES)

RM			:=	rm -rf

#
# Rules
#

all:		$(LIBNAME)

$(LIBNAME): $(OBJS)
	@ar rc $@.a $^
	@echo " $(GREEN)$(BOLD)$(ITALIC)■$(RESET)  linking	$(GRAY)$(BOLD)$(ITALIC)$(LIBNAME).a$(RESET)"

so:			$(SOBJS)
	@$(CC) -shared -o $(LIBNAME).so $^
	@echo " $(GREEN)$(BOLD)$(ITALIC)■$(RESET)  linking	$(GRAY)$(BOLD)$(ITALIC)$(LIBNAME).so$(RESET)"

$(OBJS_DIR)/PIC/%.o: %.c
	@mkdir -p $(@D)
	@echo " $(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)(PIC)$(notdir $@) from $(GRAY)$(BOLD)$(ITALIC)$(notdir $^)$(RESET)"
	@$(CC) $(CFLAGS) -fPIC $(COPTS) -o $@ -c $^

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo " $(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$(notdir $@) from $(GRAY)$(BOLD)$(ITALIC)$(notdir $^)$(RESET)"
	@$(CC) $(CFLAGS) $(COPTS) -o $@ -c $^

clean:
	@if [ -d $(OBJS_DIR) ]; then \
		echo " $(RED)$(BOLD)$(ITALIC)■$(RESET)  deleted	$(GRAY)$(BOLD)$(ITALIC)$(OBJS_DIR)$(RESET)"; \
		$(RM) $(OBJS_DIR); \
	fi

fclean:		clean
	@if [ -f "$(LIBNAME).a" ]; then \
		echo " $(RED)$(BOLD)$(ITALIC)■$(RESET)  deleted	$(GRAY)$(BOLD)$(ITALIC)$(LIBNAME).a$(RESET)"; \
		$(RM) $(LIBNAME).a; \
	fi;
	@if [ -f "$(LIBNAME).so" ]; then \
		echo " $(RED)$(BOLD)$(ITALIC)■$(RESET)  deleted	$(GRAY)$(BOLD)$(ITALIC)$(LIBNAME).so$(RESET)"; \
		$(RM) $(LIBNAME).so; \
	fi;

test:		all
	@$(CC) -o $(LIBNAME)_test $(LIBNAME)_test.c $(LIBNAME).a $(COPTS) $(CFLAGS)
	@./$(LIBNAME)_test

re:			fclean all

.PHONY:		all clean fclean re

#
# COLORS
# 

BOLD			=	\033[1m
ITALIC			=	\033[3m

BLACK			=	\033[30m
RED				=	\033[31m
GREEN			=	\033[32m
YELLOW			=	\033[33m
BLUE			=	\033[34m
MAGENTA			=	\033[35m
CYAN			=	\033[36m
WHITE			=	\033[37m
GRAY			=	\033[90m

RESET			=	\033[0m

LINE_CLR		=	\33[2K\r
