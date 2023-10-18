# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/09/25 13:26:38 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a
I			=	./ ./libft/
D			=	dep/
O			=	obj/
L			=	./libft/

SRC			=	ft_printf.c \
				ft_putnbr_base_fd.c \
				ft_putnchar_fd.c \
				ft_putnstr_fd.c \
				print_char.c \
				print_nbr.c \
				print_ptr.c \
				print_str.c

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(foreach X,$I,-I$X)
ARFLAGS		=	rcs

DEP			=	$(SRC:%.c=$D%.d)
OBJ			=	$(SRC:%.c=$O%.o)

.PHONY:			all cleandep cleanobj clean fclean re

all:			$(NAME)

$(NAME):		$(OBJ)
				make -C $L
				cp $Llibft.a ./$@
				ar $(ARFLAGS) $(NAME) $^

$(OBJ): $O%.o:	%.c | $O
				$(CC) $(CFLAGS) -c $< -o $@

$(DEP): $D%.d:	%.c | $D
				@$(CC) $(CFLAGS) -MM -MP -MF $@ -MT "$O$*.o $@" $<

$O $D:
				@mkdir -p $@

cleandep:
ifeq ($(filter $(MAKECMDGOALS),clean fclean re),)
				make -C $L cleandep
endif
				rm -rf $D

cleanobj:
ifeq ($(filter $(MAKECMDGOALS),clean fclean re),)
				make -C $L cleanobj
endif
				rm -rf $O

clean:			cleandep cleanobj
ifeq ($(filter $(MAKECMDGOALS),fclean re),)
				make -C $L clean
endif

fclean:			clean
				make -C $L fclean
				rm -f $(NAME)

re:				fclean all

ifeq ($(filter $(MAKECMDGOALS),cleandep cleanobj clean fclean),)
-include 		$(DEP)
endif