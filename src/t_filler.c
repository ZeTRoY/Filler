/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_filler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:58:48 by aroi              #+#    #+#             */
/*   Updated: 2019/02/25 19:37:32 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler		*ft_create_filler(void)
{
	t_filler	*new;

	if ((new = (t_filler *)malloc(sizeof(t_filler))) == NULL)
		return (NULL);
	new->m = 0;
	new->n = 0;
	new->map = NULL;
	if ((new->piece = (t_piece *)malloc(sizeof(t_piece))) == NULL ||
		(new->shape = (t_shape *)malloc(sizeof(t_shape))) == NULL)
		return (NULL);
	new->sum = 1000000;
	new->piece->len[0] = 0;
	new->piece->len[1] = 0;
	new->coord[0] = 0;
	new->coord[1] = 0;
	return (new);
}

static void		free_structures(t_filler *filler)
{
	int i;

	i = 0;
	while (i < filler->m)
	{
		free(filler->map[i]);
		free(filler->board[i++]);
	}
	free(filler->map);
	free(filler->board);
	i = 0;
	while (i < filler->piece->len[1])
		free(filler->piece->piece[i++]);
	free(filler->piece->piece);
	i = 0;
	while (i < filler->shape->coord[1][0] - filler->shape->coord[0][0] + 1)
		free(filler->shape->shape[i++]);
	free(filler->shape->shape);
}

void			ft_refresh_filler(t_filler *filler)
{
	free_structures(filler);
	filler->map = NULL;
	filler->sum = 1000000;
	filler->piece->len[0] = 0;
	filler->piece->len[1] = 0;
	filler->coord[0] = 0;
	filler->coord[1] = 0;
	filler->m = 0;
	filler->n = 0;
}
