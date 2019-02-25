/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:50:03 by aroi              #+#    #+#             */
/*   Updated: 2019/02/25 18:50:34 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	make_board(t_filler *filler)
{
	int i;
	int j;

	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == '.')
			{
				filler->board[i][j].aroi = BIG_NUMBER;
				filler->board[i][j].opponent = BIG_NUMBER;
			}
			else
			{
				filler->board[i][j].aroi = 0;
				filler->board[i][j].opponent = 0;
			}
			j++;
		}
		i++;
	}
}
