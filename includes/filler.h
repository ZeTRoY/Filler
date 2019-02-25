/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:38:34 by aroi              #+#    #+#             */
/*   Updated: 2019/02/25 19:46:32 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"

# define BIG_NUMBER 10101
# define ABS(x)	(((x) > 0) ? (x) : -(x))

/*
**  t_board				- structure for a cell on a board with the shortest
**					distance from cells with my (aroi) mark to this cell and
**				 	from cells with opponent's mark to this cell.
**
**  int aroi			- the shortest distance from aroi's cells
**					to the one you're located on.
**  int opponent		- the shortest distance from opponent's cells
**					to the one you're located on.
*/

typedef struct	s_board
{
	int			aroi;
	int			opponent;
}				t_board;

/*
**  t_piece				- structure, where you can find a piece (token)
**  				and it's size.
**
**  int coord[2]		- here you can find two numbers:
**     - coord[0] 		- quantity of piece's rows;
**     - coord[1] 		- quantity of piece's columns.
**  char **piece		- an array with a piece (token) in it.
**					Size is coord[0] * coord[1].
*/

typedef struct	s_piece
{
	int			len[2];
	char		**piece;
}				t_piece;

/*
**  t_shape				- structure, where you can find a shape of a piece
**					(i.e. a piece of the token with stars).
**
**  char **shape		- a piece with stars. Size is :
**			(coord[1][0] - coord[0][0] + 1) * (coord[1][1] - coord[0][1] + 1)
**  int coord[2][2] 	- an array where is stored min and max coordinates
**					of a piece array where you can find a shape
**					(i.e. an array made of stars). Meanings of:
**     - coord[0][0]	- min coordinate of row in piece array;
**     - coord[0][1]	- min coordinate of column in piece array;
**     - coord[1][0]	- max coordinate of row in piece array;
**     - coord[1][1]	- max coordinate of column in piece array;
**
**				TIP:
**	So as you can see, we can count qunatity of rows and columns of our shape:
**		by the y axis (rows) as			coord[1][0] - coord[0][0] + 1;
**		by the x axis (columns) as		coord[1][1] - coord[0][1] + 1.
*/

typedef struct	s_shape
{
	int			coord[2][2];
	char		**shape;
}				t_shape;

/*
**  t_coord				- structure to store coordinates of some object.
**
**  int x				- x-coordinate.
**  int y				- y-coordinate, respectively.
*/

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

/*
**  t_filler			- structure, where you can find min sum of board's cells
**					where the shape can fit, my and opponent's characters
**					on the map, map's size, the map, final coordinates
**					as the answer of filler player, a piece, a shape
**					and board with distances.
**
**  int sum				- a min sum of cells on board where shape can fit.
**  char aroi			- a mark which determines your cells on the map.
**  char opponent		- a mark which determines opponent's cells on the map.
**  int m				- a quantity of map's rows.
**  int n				- a quantity of map's columns.
**  int coord[2]		- coordinates where you put you piece:
**      - coord[0]		- coordinate of row in piece and map array;
**      - coord[1]		- coordinate of column in piece and map array.
**  char **map			- a map where you can see '.' as empty cells,
**					aroi's character as my (aroi) cells and
**					opponent's character as opponent's cells.
**  t_piece *piece		- a structure with piece in it.
**	t_shape *shape		- a structure with shape of piece in it.
**	t_board **board		- two-dimensional array where each cell contains of
**					aroi's and opponent's distance
**					to it's nearest mark character.
*/

typedef struct	s_filler
{
	char		aroi;
	char		opponent;
	int			m;
	int			n;
	int			sum;
	int			coord[2];
	char		**map;
	t_piece		*piece;
	t_shape		*shape;
	t_board		**board;
}				t_filler;

t_filler		*ft_create_filler(void);
void			ft_refresh_filler(t_filler *filler);
void			check_first_line(char *line, t_filler *filler);
int				get_size(char *line, t_filler *filler);
void			get_map(char *line, t_filler *filler);
void			get_size_of_piece(char *line, t_filler *filler);
void			get_piece(t_filler *filler, char *line);
void			make_board(t_filler *filler);
void			calculate_distances(t_filler *filler);
void			get_distances_for_players(t_filler *filler);
void			get_distance_to_cell(t_filler *filler, int x, int y);
void			find_to_place(t_filler *filler);
void			place_piece(t_filler *filler, t_coord board, t_coord shape);
int				exit_func(char *str);

#endif
