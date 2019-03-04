# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 18:27:46 by aroi              #+#    #+#              #
#    Updated: 2019/03/04 15:10:08 by aroi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	visualizer

FILES	=	main \
			parse_options \
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

