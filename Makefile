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

.PHONY:			all bonus clean fclean re libft

all:			$(NAME)

$(NAME):		$(OBJ)
				make -C $L
				cp $Llibft.a ./$@
				ar $(ARFLAGS) $(NAME) $^

bonus:			$(OBJ) $(OBJBONUS)


$(OBJ): $O%.o:	%.c | $O
				$(CC) $(CFLAGS) -c $< -o $@

$(DEP): $D%.d:	%.c | $D
				@$(CC) $(CFLAGS) -MM -MP -MF $@ -MT "$O$*.o $@" $<

$O $D:
				@mkdir -p $@

cleandep:
				rm -f $(wildcard $(DEP))

cleandepdir:	cleandep
				rm -rf $D

cleanobj:
				rm -f $(wildcard $(OBJ))

cleanobjdir:	cleanobj
				rm -rf $O

clean:			cleandepdir cleanobjdir

fclean:			clean
				rm -f $(NAME)

re:				fclean all

-include 		$(DEP)
