/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_names.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:57:10 by aroi              #+#    #+#             */
/*   Updated: 2019/03/02 16:26:39 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static char	*get_name_of_player(char *player)
{
	char *line;
	char *tmp;
	char *name;

	if (get_next_line(STDIN_FILENO, &line) < 0 || line == NULL)
		exit_func("Bad name input (1)");
	while (ft_strstr(line, "$$$ exec") == NULL ||
		ft_strstr(line, player) == NULL)
	{
		ft_strdel(&line);
		if (get_next_line(STDIN_FILENO, &line) < 0 || line == NULL)
			exit_func("Bad name input (2)");
	}
	tmp = ft_strchr(line, ':') + 1;
	while (*tmp == ' ')
		tmp++;
	name = ft_strsub(tmp, ft_strrchr(tmp, '/') - tmp + 1,
		ft_strrchr(tmp, '.') - ft_strrchr(tmp, '/') - 1);
	ft_strdel(&line);
	return (name);
}

void		get_names(t_visual *vis)
{
	vis->p1_name = get_name_of_player("p1");
	vis->p2_name = get_name_of_player("p2");
}
