/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:31:17 by aroi              #+#    #+#             */
/*   Updated: 2019/03/04 15:04:51 by aroi             ###   ########.fr       */
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

/*
** Emojies:
*/

# define TURTLE "\xF0\x9F\x90\xA2"
# define CRAB_INVADER "\xF0\x9F\x91\xBE"
# define LANTERN "\xF0\x9F\x8F\xAE"
# define ROCKET "\xF0\x9F\x9A\x80"
# define MUSHROOM "\xF0\x9F\x8D\x84"
# define POLICEMAN "\xF0\x9F\x91\xAE"
# define JP_OGRE "\xF0\x9F\x91\xB9"

/*
**	Colors for usage:
*/

# define USAGE_BG "\033[41m"
# define AVLBL_BG "\033[48;5;127m"
# define TURTLE_CLR "\033[32m"
# define ALIEN_CLR "\033[35m"
# define LNTRN_CLR "\033[38;5;208m"
# define ROCKET_CLR "\033[38;5;222m"
# define MUSHROOM_CLR "\033[38;5;125m"
# define POLICEMAN_CLR "\033[93m"
# define OGRE_CLR "\033[31m"
# define DEFAULT_FG "\033[39m"
# define DEFAULT_BG "\033[49m"

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
**  t_options			- is a structure, which stores emoji representation of
**					player 1, player 2 and empty cells, speed integer and mark
**					to know which sound to play.
**
**  char *p1			- first player's emoji.
**  char *p2			- second player's emoji.
**  char *empty			- empty cells' emoji.
**  uint32_t speed		- value of speed, which is sent to usleep function.
**  uin8_t sound		- a mark to know which sound it should play:
**					0: no sound.
**					1: sound from ./music/chomp_1.mp3 .
**					2: sound from ./music/chomp_2.wav .
*/

typedef struct	s_options
{
	char		*p1;
	char		*p2;
	char		*empty;
	uint32_t	speed;
	uint8_t		sound;
}				t_options;

/*
**  t_visual			- is a structure, where I store quantity of rows and
**					columns of the map, ..., and a structure with quantity of
**					filled cells by players and empty cells etc.
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
**  t_options options	- a structure, which stores emoji representation of
**					player 1, player 2 and empty cells, speed integer and mark
**					to know which sound to play.
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
	t_options	options;
}				t_visual;

void			ft_parse_options(int argc, char **argv, t_visual *vis);
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
