/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:26:03 by aroi              #+#    #+#             */
/*   Updated: 2019/03/04 11:15:33 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static void	get_signature(t_visual *vis)
{
	int		len;

	len = ft_strlen(vis->p1_name) > ft_strlen(vis->p2_name) ?
		ft_strlen(vis->p1_name) : ft_strlen(vis->p2_name);
	vis->signature = create_win(5, 4 + 2 + 3 + len + 3, 0, vis->n * 2 + 35);
	mvwaddstr(vis->signature, 1, 1, "p1: ");
	mvwaddstr(vis->signature, 1, 5, vis->options.p1);
	mvwaddstr(vis->signature, 1, 7, " - ");
	mvwaddstr(vis->signature, 1, 10, vis->p1_name);
	mvwaddstr(vis->signature, 2, 1, "p2: ");
	mvwaddstr(vis->signature, 2, 5, vis->options.p2);
	mvwaddstr(vis->signature, 2, 7, " - ");
	mvwaddstr(vis->signature, 2, 10, vis->p2_name);
	mvwaddstr(vis->signature, 3, 1, "    ");
	mvwaddstr(vis->signature, 3, 5, vis->options.empty);
	mvwaddstr(vis->signature, 3, 7, " - empty");
}

static void	get_score(t_visual *vis)
{
	int		i;
	char	*tmp;

	vis->score = create_win(vis->m + 2, 20, 0, vis->n * 2 + 10);
	i = -1;
	while (++i < vis->m * vis->filler.p1 / vis->m / vis->n)
		mvwaddstr(vis->score, vis->m - i - 1, 3, vis->options.p1);
	mvwaddstr(vis->score, vis->m, 3, (tmp = ft_itoa(vis->filler.p1)));
	ft_strdel(&tmp);
	i = -1;
	while (++i < vis->m * vis->filler.p2 / vis->m / vis->n)
		mvwaddstr(vis->score, vis->m - i - 1, 9, vis->options.p2);
	mvwaddstr(vis->score, vis->m, 9, (tmp = ft_itoa(vis->filler.p2)));
	ft_strdel(&tmp);
	i = -1;
	while (++i < vis->m * vis->filler.empty / vis->m / vis->n)
		mvwaddstr(vis->score, vis->m - i - 1, 15, vis->options.empty);
	mvwaddstr(vis->score, vis->m, 15, (tmp = ft_itoa(vis->filler.empty)));
	ft_strdel(&tmp);
}

static void	refresh_filler(t_visual *vis)
{
	vis->filler.empty = 0;
	vis->filler.p1 = 0;
	vis->filler.p2 = 0;
}

void		read_and_draw(t_visual *vis, char **line, char **map)
{
	while (1)
	{
		signal(SIGWINCH, resize_handler);
		if (ft_strstr(*line, "Plateau"))
		{
			refresh_filler(vis);
			map = get_map(vis, line);
			initialise_window(vis);
			draw_map(vis, map);
			del_map(map);
			get_score(vis);
			get_signature(vis);
			wrefresh(vis->map);
			wrefresh(vis->score);
			wrefresh(vis->signature);
			usleep(vis->options.speed);
			delwin(vis->map);
			delwin(vis->score);
			delwin(vis->signature);
		}
		ft_strdel(line);
		if (get_next_line(STDIN_FILENO, line) == 0)
			break ;
	}
	ft_strdel(line);
}
