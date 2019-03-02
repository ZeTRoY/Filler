# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 18:27:46 by aroi              #+#    #+#              #
#    Updated: 2019/03/02 15:08:38 by aroi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	visualizer

FILES	=	main \
			window \
			get_names \
			read \
			map \
			show_winner \
			exit

HEADERS	=	-I ./includes/ -I ../libft/includes

SRC		=	$(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ		=	$(addprefix obj/, $(addsuffix .o, $(FILES)))

obj/%.o: src/%.c
	gcc -o $@ -c $^ $(HEADERS)

all: $(NAME) ./includes/visual.h

$(NAME): ../libft/libft.a $(OBJ)
	gcc $(OBJ) $(HEADERS) -L ../libft -lft -lncurses -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

