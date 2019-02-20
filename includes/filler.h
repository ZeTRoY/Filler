/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:38:34 by aroi              #+#    #+#             */
/*   Updated: 2019/02/20 17:06:27 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"

# define BIG_NUMBER 25

typedef struct s_board
{
	int 		distance;
	int			sought;
}				t_board;

typedef struct	s_piece
{
	int			x;
	int			y;
	char		**piece;
}				t_piece;

typedef struct  s_filler{
	char		playermark;
	int			m;
	int			n;
	int			coord[2];
	char		**map;
	t_piece		*piece;
	t_board		**board;
}               t_filler;

t_filler		*ft_create_filler(void);
void			ft_destroy_filler(t_filler **filler);
#endif
