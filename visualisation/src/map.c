/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:25:57 by aroi              #+#    #+#             */
/*   Updated: 2019/03/04 15:05:53 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static int	get_color(char *str)
{
	if (ft_strequ(str, TURTLE))
		return (1);
	else if (ft_strequ(str, CRAB_INVADER))
		return (2);
	else if (ft_strequ(str, LANTERN) || ft_strequ(str, JP_OGRE) ||
			ft_strequ(str, MUSHROOM) || ft_strequ(str, ROCKET))
		return (4);
	else
		return (5);
}

static void	put_char(t_visual *vis, char **map, int i, int j)
{
	if (map[i][j] == '.')
	{
		mvwaddstr(vis->map, i + 1, j * 2 + 1, vis->options.empty);
		vis->filler.empty++;
	}
	else if (map[i][j] == 'o' || map[i][j] == 'O')
	{
		if (map[i][j] == 'o')
			wattron(vis->map, COLOR_PAIR(get_color(vis->options.p1)));
		mvwaddstr(vis->map, i + 1, j * 2 + 1, vis->options.p1);
		vis->filler.p1++;
		wattroff(vis->map, COLOR_PAIR(get_color(vis->options.p1)));
	}
	else
	{
		if (map[i][j] == 'x')
			wattron(vis->map, COLOR_PAIR(get_color(vis->options.p2)));
		mvwaddstr(vis->map, i + 1, j * 2 + 1, vis->options.p2);
		vis->filler.p2++;
		wattroff(vis->map, COLOR_PAIR(get_color(vis->options.p2)));
	}
}

void		draw_map(t_visual *vis, char **map)
{
	int i;
	int j;

	i = -1;
	while (++i < vis->m)
	{
		j = -1;
		while (++j < vis->n)
			put_char(vis, map, i, j);
	}
	if (vis->options.sound)
		vis->options.sound == 1 ? system("afplay -v 0.8 ./music/chomp_1.mp3 &")
			: system("afplay -v 0.8 ./music/chomp_2.wav &");
}

void		del_map(char **map)
{
	int i;

	i = -1;
	if (map == NULL || *map == NULL)
		return ;
	while (map[++i])
		ft_strdel(&map[i]);
	free(map);
}

char		**get_map(t_visual *vis, char **line)
{
	char	**map;
	int		i;
	int		j;

	vis->m = ft_atoi(*line + 8);
	map = (char **)malloc(sizeof(char *) * (vis->m + 1));
	vis->n = ft_atoi(*line + 8 + ft_count_digits_base(vis->m, 10) + 1);
	ft_strdel(line);
	get_next_line(STDIN_FILENO, line);
	i = -1;
	while (++i < vis->m)
	{
		j = 0;
		ft_strdel(line);
		get_next_line(STDIN_FILENO, line);
		while (*(*line + j) >= '0' && *(*line + j) <= '9')
			j++;
		map[i] = ft_strdup(*line + j + 1);
	}
	map[i] = NULL;
	ft_strdel(line);
	return (map);
}
