/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_of_distances.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:06:32 by aroi              #+#    #+#             */
/*   Updated: 2019/02/25 19:04:04 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	get_distances(t_filler *filler, char player, int i, int j)
{
	int x;
	int y;

	x = 0;
	while (x < filler->m)
	{
		y = 0;
		while (y < filler->n)
		{
			if (player == filler->aroi)
			{
				if (filler->board[x][y].aroi > ABS(x - i) + ABS(y - j))
					filler->board[x][y].aroi = ABS(x - i) + ABS(y - j);
			}
			else
			{
				if (filler->board[x][y].opponent > ABS(x - i) + ABS(y - j))
					filler->board[x][y].opponent = ABS(x - i) + ABS(y - j);
			}
			y++;
		}
		x++;
	}
}

void		get_distance_to_cell(t_filler *filler, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->board[i][j].aroi > ABS(x - i) + ABS(y - j))
				filler->board[i][j].aroi = ABS(x - i) + ABS(y - j);
			if (ft_toupper(filler->map[i][j]) == filler->opponent)
				get_distances(filler, filler->opponent, i, j);
			j++;
		}
		i++;
	}
}

void		get_distances_for_players(t_filler *filler)
{
	int i;
	int j;

	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == filler->aroi)
				get_distances(filler, filler->aroi, i, j);
			else if (ft_toupper(filler->map[i][j]) == filler->opponent)
				get_distances(filler, filler->opponent, i, j);
			j++;
		}
		i++;
	}
}
