/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:31:17 by aroi              #+#    #+#             */
/*   Updated: 2019/03/02 17:00:16 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <locale.h>
# include <curses.h>
# include <signal.h>
# include "libft.h"
# include "get_next_line.h"

# define ESC_KEY 27
# define PLAYER_ONE "\xF0\x9F\x90\xA2"
# define PLAYER_TWO "\xF0\x9F\x91\xBE"
# define EMPTY "\xF0\x9F\x8D\x84"

/*
**  t_filled			- is a structure, where I store 3 integers:
**					first player's, second player's and empty cells on the map.
**
**  int p1				- quantity of first player's cells on the map.
**  int p2				- quantity of second player's cells on the map.
**  int empty			- quantity of empty cells on the map.
**
**  			TIP:
**
**  Sum of p1, p2 and empty is quantity of cells on the map,
**  	i.g. 	p1 + p2+ empty = vis->m * vis->n.
*/

typedef struct	s_filled
{
	int			p1;
	int			p2;
	int			empty;
}				t_filled;

/*
**  t_visual			- is a structure, where I store quantity of rows and
**					columns of the map, ..., and a structure with quantity of
**					filled cells by players and empty cells.
**
**  int m				- quantity of rows of the map.
**  int n				- quantity of columns of the map.
**  char *p1_name		- name of the first player. If the binary is called
**					'abanlin.filler', then p1_name will be "abanlin".
**  char *p2_name		- name of the second player. The same as for p1_name.
**  t_filled filler		- a structure with quantity of empty and
**					filled by player1 & player2 cells.
**  WINDOW *map			- window of ncurses with graphical representation of map
**  WINDOW *score		- window of ncurses with graphical representation of
**					quantity of filled cells (empty and by players) of the map.
**  WINDOW *winner		- window of ncurses with graphical represantion
**					of the winner.
**  WINDOW *signature	- window of ncurses where you can find how this binary
**					depicts players' and empty cells on the map. Also it has
**					players' siganture.
*/

typedef struct	s_visual
{
	int			m;
	int			n;
	char		*p1_name;
	char		*p2_name;
	t_filled	filler;
	WINDOW		*map;
	WINDOW		*score;
	WINDOW		*winner;
	WINDOW		*signature;
}				t_visual;

WINDOW			*create_win(int height, int width, int x, int y);
void			get_names(t_visual *vis);
void			read_and_draw(t_visual *vis, char **line, char **map);
void			initialise_window(t_visual *vis);
void			resize_handler(int sig);
char			**get_map(t_visual *vis, char **line);
void			del_map(char **map);
void			draw_map(t_visual *vis, char **map);
void			show_winner(t_visual *vis);
int				exit_func(char *str);

#endif
