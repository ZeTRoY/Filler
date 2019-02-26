/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:57:01 by aroi              #+#    #+#             */
/*   Updated: 2019/02/26 12:26:28 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	check_answer(t_filler *filler, int sum, int dx, int dy)
{
	if (filler->sum > sum)
	{
		filler->sum = sum;
		filler->coord[0] = dx;
		filler->coord[1] = dy;
	}
}

static int	check_cell(t_filler *filler, int dx, int dy, int *placed)
{
	if (ft_toupper((filler->map[dx][dy]) == filler->opponent)
		|| (filler->map[dx][dy] == filler->aroi && *placed))
		return (-1);
	if (filler->map[dx][dy] == filler->aroi)
		*placed = 1;
	return (filler->board[dx][dy].aroi + filler->board[dx][dy].opponent);
}

void		place_piece(t_filler *filler, t_coord board, t_coord shape)
{
	int i;
	int j;
	int	placed;
	int	sum;
	int tmp;

	sum = 0;
	i = -1;
	placed = 0;
	while (++i <= filler->shape->coord[1][0] - filler->shape->coord[0][0])
	{
		j = -1;
		while (++j <= filler->shape->coord[1][1] - filler->shape->coord[0][1])
		{
			if (filler->shape->shape[i][j] == '*')
			{
				if ((tmp = check_cell(filler, board.x - shape.x + i,
					board.y - shape.y + j, &placed)) < 0)
					return ;
				else
					sum += tmp;
			}
		}
	}
	check_answer(filler, sum, board.x - shape.x, board.y - shape.y);
}
