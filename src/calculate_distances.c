/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distances.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:09:58 by aroi              #+#    #+#             */
/*   Updated: 2019/03/02 18:02:12 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_path(t_filler *filler, int xaroi)
{
	int i;

	i = 0;
	while (i < xaroi)
	{
		if (ft_tolower(filler->map[i][filler->n - 1]) == filler->opponent)
			return (0);
		i++;
	}
	return (1);
}

static int	check_height(t_filler *filler, int *xaroi, int *xopp)
{
	int	i;

	i = 0;
	*xaroi = -1;
	*xopp = -1;
	while (i < filler->m)
	{
		if (*xaroi == -1 && ft_strchr(filler->map[i], filler->aroi))
			*xaroi = i;
		if (*xopp == -1 && (ft_strchr(filler->map[i], filler->opponent) ||
				ft_strchr(filler->map[i], ft_tolower(filler->opponent))))
			*xopp = i;
		if (*xaroi > -1 && *xopp > -1)
			break ;
		i++;
	}
	if (*xaroi == -1)
		return (*xaroi);
	else if (*xaroi >= *xopp && *xaroi != 0)
		return (0);
	return (1);
}

void		calculate_distances(t_filler *filler)
{
	int i;
	int xaroi;
	int xopp;

	make_board(filler);
	i = check_height(filler, &xaroi, &xopp);
	if (i == -1)
		return ;
	if (filler->m < 20 || filler->n < 20)
	{
		if (i == 0)
		{
			if (check_path(filler, xaroi) == 1)
				get_distance_to_cell(filler, 0, filler->n - 1);
			else
				get_distance_to_cell(filler, filler->m - 1, 0);
		}
		else if (xaroi < xopp)
			get_distance_to_cell(filler, xopp - 1, 0);
		else
			get_distances_for_players(filler);
	}
	else
		get_distances_for_players(filler);
}
