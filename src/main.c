/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:37:58 by aroi              #+#    #+#             */
/*   Updated: 2019/02/26 12:27:11 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			main(void)
{
	char		*line;
	t_filler	*filler;

	line = NULL;
	filler = ft_create_filler();
	check_first_line(line, filler);
	while (1)
	{
		if (get_size(line, filler) == 0)
			break ;
		if (get_next_line(0, &line) < 0 || line == NULL)
			exit_func("Bad input file (string of numbers)");
		ft_strdel(&line);
		get_map(line, filler);
		get_size_of_piece(line, filler);
		get_piece(filler, line);
		make_board(filler);
		calculate_distances(filler);
		
		// int i = 0;
		// int j;
		// while (i < filler->m)
		// {
		// 	j = 0;
		// 	while (j < filler->n)
		// 	{
		// 		ft_printf("%d ", filler->board[i][j].aroi + filler->board[i][j].opponent);
		// 		j++;
		// 	}
		// 	ft_putendl("");
		// 	i++;
		// }

		find_to_place(filler);
		ft_printf("%d %d\n", filler->coord[0] - filler->shape->coord[0][0],
			filler->coord[1] - filler->shape->coord[0][1]);
		ft_refresh_filler(filler);
	}
	return (0);
}
