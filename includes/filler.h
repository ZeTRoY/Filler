/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:38:34 by aroi              #+#    #+#             */
/*   Updated: 2019/02/21 20:05:51 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"

# define BIG_NUMBER 9876543
# define ABS(x)	(((x) > 0) ? (x) : -(x))
typedef struct s_board
{
	int			aroi;
	int			opponent;
}				t_board;

typedef struct	s_piece
{
	int			coord[2];
	char		**piece;
}				t_piece;

typedef struct	s_shape
{
	int			coord[2][2];
	char		**shape;
}				t_shape;

typedef struct  s_filler
{
	int			sum;
	char		playermark;
	int			m;
	int			n;
	int			coord[2];
	char		**map;
	t_piece		*piece;
	t_shape		*shape;
	t_board		**board; //change
}               t_filler;

t_filler		*ft_create_filler(void);
void			ft_refresh_filler(t_filler *filler);
#endif
