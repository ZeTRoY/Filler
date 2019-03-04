/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:25:41 by aroi              #+#    #+#             */
/*   Updated: 2019/03/04 11:26:01 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

WINDOW	*create_win(int height, int width, int x, int y)
{
	WINDOW *win;

	win = newwin(height, width, x, y);
	box(win, 0, 0);
	return (win);
}

void	initialise_window(t_visual *vis)
{
	vis->map = create_win(vis->m + 2, vis->n * 2 + 2, 0, 0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(3, COLOR_YELLOW, COLOR_BLUE);
	init_pair(4, COLOR_WHITE, COLOR_RED);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
}

void	resize_handler(int sig)
{
	endwin();
	refresh();
	clear();
}
