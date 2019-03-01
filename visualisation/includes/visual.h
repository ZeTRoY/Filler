/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:31:17 by aroi              #+#    #+#             */
/*   Updated: 2019/03/01 18:03:21 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# define ESC_KEY 27

/*
**  t_filled		- is a structure, where I store 3 integers: first player's,
**				second player's and empty cells on the map.
**
**  int p1			- quantity of first player's cells on the map.
**  int p2			- quantity of second player's cells on the map.
**  int empty		- quantity of empty cells on the map.
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
**  t_visual		- is a structure, where I store quantity of rows and columns
**				of the map, ..., and a structure with quantity of filled cells
**				by players and empty cells.
**
**  int m			- quantity of rows of the map.
**  int n			- quantity of columns of the map.
**  ...
**  t_filled filler	- a structure with quantity of empty and 
**				filled by player1 & player2 cells.
*/

typedef struct	s_visual
{
	int			m;
	int			n;
	int			col;
	int			row;
	char		*p1_name;
	char		*p2_name;
	t_filled	filler;
}				t_visual;

#endif
