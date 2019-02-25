/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:00:15 by aroi              #+#    #+#             */
/*   Updated: 2019/02/25 19:42:56 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	cut_shape(t_filler *filler)
{
	int i;

	filler->shape->shape = (char **)malloc(sizeof(char *) *
		(filler->shape->coord[1][0] -
			filler->shape->coord[0][0] + 2));
	i = 0;
	while (i < filler->shape->coord[1][0] -
		filler->shape->coord[0][0] + 1)
	{
		filler->shape->shape[i] =
			ft_strsub(filler->piece->piece[i + filler->shape->coord[0][0]],
				filler->shape->coord[0][1], filler->shape->coord[1][1] -
					filler->shape->coord[0][1] + 1);
		i++;
	}
	filler->shape->shape[filler->shape->coord[1][0] -
		filler->shape->coord[0][0] + 1] = NULL;
}

static void	get_minmax_of_piece(int coord[2][2], int i, int j)
{
	i < coord[0][0] ? coord[0][0] = i : 0;
	j < coord[0][1] ? coord[0][1] = j : 0;
	i > coord[1][0] ? coord[1][0] = i : 0;
	j > coord[1][1] ? coord[1][1] = j : 0;
}

void		get_piece(t_filler *filler, char *line)
{
	int i;
	int j;

	i = -1;
	while (++i < filler->piece->len[1])
	{
		if (get_next_line(0, &line) < 0)
			exit_func("Bad file input (piece)");
		filler->piece->piece[i] = ft_strdup(line);
		ft_strdel(&line);
		j = -1;
		while (++j < filler->piece->len[0])
		{
			if (filler->piece->piece[i][j] == '*')
				get_minmax_of_piece(filler->shape->coord, i, j);
		}
	}
	cut_shape(filler);
}

void		get_size_of_piece(char *line, t_filler *filler)
{
	int i;
	int j;

	get_next_line(0, &line) < 0 ? exit_func("Bad file input (piece size)") : 0;
	if (ft_strnequ(line, "Piece", 5) == 0)
		return ;
	if (*(line + 6) >= '0' && *(line + 6) <= '9')
		if ((filler->piece->len[1] = ft_atoi(line + 6)) <= 0)
			return ;
	if (*(line + 7 + ft_count_digits_base(filler->piece->len[1], 10)) >= '0' &&
		*(line + 7 + ft_count_digits_base(filler->piece->len[1], 10)) <= '9')
		if ((filler->piece->len[0] = ft_atoi(line + 7 +
			ft_count_digits_base(filler->piece->len[1], 10))) <= 0)
		{
			filler->piece->len[1] = 0;
			return ;
		}
	filler->piece->piece = (char **)malloc(sizeof(char *) *
		filler->piece->len[1]);
	ft_strdel(&line);
	filler->shape->coord[0][0] = filler->piece->len[1];
	filler->shape->coord[0][1] = filler->piece->len[0];
	filler->shape->coord[1][0] = 0;
	filler->shape->coord[1][1] = 0;
}
