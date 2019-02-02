/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:37:58 by aroi              #+#    #+#             */
/*   Updated: 2019/02/02 18:52:53 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	exit_func(char *str)
{
	ft_putendl(str);
	exit (1);
}

static int	get_piece(char *line, t_filler *filler)
{
	int i;

	i = 0;
	get_next_line(1, &line);
	if (ft_strnequ("Plateau ", line, 8) == 0)
		return (0);
	if (*(line + 8) < '0' || *(line + 8) > '9')
		return (0);
	filler->x = ft_atoi(line + 8);
	while (*(line + 8 + i) >= '0' && *(line + 8 + i) <= '9')
		i++;
	if (*(line + 8 + i) < '0' || *(line + 8 + i) > '9')
		return (0);
	filler->y = ft_atoi(line + 8 + i);
	return (1);
}

static void	check_name(char *line, t_filler *filler)
{
	int i;

	i = 0;
	if (ft_strncmp("$$$ exec ", line, 9) != 0 || *(line + 9) != 'p')
		exit_func("Bad player info");
	while(*(line + 10 + i) == ' ')
		i++;
	if (ft_atoi(line + 10 + i) == 1)
		filler->playermark = 'o';
	else if (ft_atoi(line + 10 + i) == 2)
		filler->playermark = 'x';
	else
		exit_func("Bad player info");
	i++;
	while(*(line + 10 + i) == ' ')
		i++;
	if (*(line + 10 + i++) != ':')
		exit_func("Bad player info");
	while(*(line + 10 + i) == ' ')
		i++;
	if (ft_strnequ(line + 10 + i, "aroi", 4) == 0 || *(line + 14 + i) != '\0')
		exit_func("Bad player info");
}

int			main(void)
{
	char		*line;
	t_filler	*filler;

	write(1, "l\n", 2);
	line = NULL;
	filler = ft_create_filler();
	if (get_next_line(1, &line) != 1 || line == NULL)
		exit_func("Bad player info (err 1)");
	check_name(line, filler);
	while (1)
	{
		ft_strdel(&line);
		if (get_piece(line, filler) == 0)
		{
			write(1, "kek\n", 4);
			ft_strdel(&line);
			break;
		}
	}
	return (0);
}
