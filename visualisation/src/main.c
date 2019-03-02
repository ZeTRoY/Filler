/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:01:37 by aroi              #+#    #+#             */
/*   Updated: 2019/03/02 17:44:09 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int		main(void)
{
	char		*line;
	char		**map;
	t_visual	vis;

	line = NULL;
	setlocale(LC_ALL, "");
	if (!initscr())
		exit_func("Screen initialisation problem.");
	curs_set(0);
	cbreak();
	noecho();
	get_names(&vis);
	if (get_next_line(STDIN_FILENO, &line) < 0 || !line)
		exit_func("Bad map input (0)");
	read_and_draw(&vis, &line, map);
	show_winner(&vis);
	freopen("/dev/tty", "r", stdin);
	while (wgetch(vis.winner) != ESC_KEY)
		continue;
	endwin();
	return (0);
}
