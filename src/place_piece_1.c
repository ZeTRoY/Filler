/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:50:09 by aroi              #+#    #+#             */
/*   Updated: 2019/02/25 19:25:53 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	ft_check_piece(t_filler *filler, int xb, int yb, t_coord shape)
{
	int		xlen;
	int		ylen;

	xlen = filler->shape->coord[1][0] - filler->shape->coord[0][0];
	ylen = filler->shape->coord[1][1] - filler->shape->coord[0][1];
	if (xb - shape.x < 0 ||
			yb - shape.y < 0 ||
				xb + xlen + 1 - shape.x > filler->m ||
					yb + ylen + 1 - shape.y > filler->n)
		return (0);
	return (1);
}

static void	find_place(t_filler *filler, int xshape, int yshape)
{
	int		i;
	int		j;
	t_coord	shape;
	t_coord	board;

	i = 0;
	shape.x = xshape;
	shape.y = yshape;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == filler->aroi &&
				ft_check_piece(filler, i, j, shape))
			{
				board.x = i;
				board.y = j;
				place_piece(filler, board, shape);
			}
			j++;
		}
		i++;
	}
}

void		find_to_place(t_filler *filler)
{
	int i;
	int j;

	i = -1;
	while (++i <= filler->shape->coord[1][0] - filler->shape->coord[0][0])
	{
		j = -1;
		while (++j <= filler->shape->coord[1][1] - filler->shape->coord[0][1])
		{
			if (filler->shape->shape[i][j] == '*')
				find_place(filler, i, j);
		}
	}
}
