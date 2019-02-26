/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_name_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 17:57:08 by aroi              #+#    #+#             */
/*   Updated: 2019/02/26 12:17:08 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_map(char *line, t_filler *filler)
{
	int i;
	int j;

	i = 0;
	filler->map = (char **)malloc(sizeof(char *) * filler->m);
	filler->board = (t_board **)malloc(sizeof(t_board *) * filler->m);
	while (i < filler->m)
	{
		j = 0;
		if (get_next_line(0, &line) < 0 || line == NULL)
			exit_func("Bad file input (map)");
		while (*(line + j) >= '0' && *(line + j) <= '9')
			j++;
		j++;
		filler->map[i] = ft_strdup(line + j);
		filler->board[i++] = (t_board *)malloc(sizeof(t_board) * filler->n);
		ft_strdel(&line);
	}
}

int			get_size(char *line, t_filler *filler)
{
	int i;

	i = 0;
	get_next_line(0, &line) < 0 || line == NULL ? exit_func("Bad input") : 0;
	if (ft_strnequ("Plateau ", line, 8) == 0)
	{
		ft_strdel(&line);
		return (0);
	}
	if (*(line + 8) < '0' || *(line + 8) > '9')
	{
		ft_strdel(&line);
		return (0);
	}
	filler->m = ft_atoi(line + 8);
	while (*(line + 8 + i) >= '0' && *(line + 8 + i) <= '9')
		i++;
	if (++i && (*(line + 8 + i) < '0' || *(line + 8 + i) > '9'))
	{
		ft_strdel(&line);
		return (0);
	}
	filler->n = ft_atoi(line + 8 + i);
	ft_strdel(&line);
	return (1);
}

static void	skip_whitespaces(char *line, int *i)
{
	while (*(line + *i) == ' ')
		(*i)++;
}

static void	check_number_of_player(t_filler *filler, char *line)
{
	if (ft_atoi(line) == 1)
	{
		filler->aroi = 'O';
		filler->opponent = 'X';
	}
	else if (ft_atoi(line) == 2)
	{
		filler->aroi = 'X';
		filler->opponent = 'O';
	}
	else
		exit_func("Bad player info");
}

void		check_first_line(char *line, t_filler *filler)
{
	int i;

	i = 0;
	if (get_next_line(0, &line) < 0 || line == NULL)
		exit_func("Bad input file (exec)");
	if (ft_strncmp("$$$ exec ", line, 9) != 0 || *(line + 9) != 'p')
		exit_func("Bad player info");
	skip_whitespaces(line + 10, &i);
	check_number_of_player(filler, line + 10 + i);
	i++;
	skip_whitespaces(line + 10, &i);
	if (*(line + 10 + i++) != ':')
		exit_func("Bad player info");
	skip_whitespaces(line + 10, &i);
	if (ft_strstr(line + 10 + i, "aroi.filler") == NULL)
		exit_func("Bad player info");
	ft_strdel(&line);
}
