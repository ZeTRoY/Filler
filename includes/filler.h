/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:38:34 by aroi              #+#    #+#             */
/*   Updated: 2019/02/04 13:34:59 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"

typedef struct  s_filler{
	char		playermark;
	int			x;
	int			y;
	int			**map;
}               t_filler;

t_filler		*ft_create_filler(void);
#endif
