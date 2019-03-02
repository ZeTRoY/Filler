/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_winner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:26:10 by aroi              #+#    #+#             */
/*   Updated: 2019/03/02 16:26:11 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static void	create_winner_window(t_visual *vis, int len)
{
	vis->winner = create_win(7, len + 8 + 7, vis->m / 2 - 2, vis->n * 2 + 35);
	wattron(vis->winner, A_BOLD | COLOR_PAIR(3));
}

static int	get_length(t_visual *vis)
{
	int len;

	if (vis->filler.p1 > vis->filler.p2)
	{
		len = ft_strlen(vis->p1_name);
		create_winner_window(vis, len);
		mvwaddstr(vis->winner, 3, 4, vis->p1_name);
	}
	else
	{
		len = ft_strlen(vis->p2_name);
		create_winner_window(vis, len);
		mvwaddstr(vis->winner, 3, 4, vis->p2_name);
	}
	return (len);
}

static void	get_frame(t_visual *vis, int len)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	while (++i < 7)
	{
		if (i == 3)
			continue;
		j = 0;
		while (j < 8 + len + 7)
		{
			if ((i == 2 || i == 4) && j > 2 && j < 8 + len + 4)
				str = "  ";
			else
				str = "\xF0\x9F\x8E\x89";
			mvwaddstr(vis->winner, i, j, str);
			j += 2;
		}
	}
}

void		show_winner(t_visual *vis)
{
	int		len;

	len = get_length(vis);
	get_frame(vis, len);
	mvwaddstr(vis->winner, 3, 1, "\xF0\x9F\x8E\x89");
	mvwaddstr(vis->winner, 3, 3, " ");
	if (len % 2 == 0)
		mvwaddstr(vis->winner, 3, 4 + len, " wins! \xF0\x9F\x8E\x89");
	else
		mvwaddstr(vis->winner, 3, 4 + len, "  wins! \xF0\x9F\x8E\x89");
	wattroff(vis->winner, A_BOLD | COLOR_PAIR(3));
	wborder(vis->winner, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(vis->winner);
}
