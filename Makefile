# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/01 13:22:06 by aroi              #+#    #+#              #
#    Updated: 2019/02/25 19:07:40 by aroi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	aroi.filler
FLAGS	=	-Wall -Werror -Wextra

FILES	=	main \
			error \
			t_filler \
			read_name_map \
			read_piece \
			make_board \
			calculate_distances \
			calculations_of_distances \
			place_piece_1 \
			place_piece_2

HEADERS	=	-I ./includes/ -I ./libft/includes

SRC		=	$(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ		=	$(addprefix obj/, $(addsuffix .o, $(FILES)))

obj/%.o: src/%.c
	gcc -o $@ -c $^ $(HEADERS)

all: $(NAME) ./includes/filler.h

$(NAME): libft/libft.a $(OBJ)
	gcc $(OBJ) $(FLAGS) $(HEADERS) -L libft -lft -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
