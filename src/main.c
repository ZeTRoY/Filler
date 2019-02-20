/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:37:58 by aroi              #+#    #+#             */
/*   Updated: 2019/02/20 11:10:10 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	exit_func(char *str)
{
	ft_putendl(str);
	exit (1);
}

void		get_distances(t_filler *filler, int board[filler->m][filler->n],
					int i, int j, int num)
{
	int temp;

	if (num > (filler->m - 1) + (filler->n - 1))
		return ;
	if (i > 0)
	{
		num + 1 < board[i - 1][j] ? board[i - 1][j] = num + 1 : 0;
		get_distances(filler, board, i - 1, j, num + 1);
	}
	if (i < filler->m - 1)
	{
		num + 1 < board[i + 1][j] ? board[i + 1][j] = num + 1 : 0;
		get_distances(filler, board, i + 1, j, num + 1);
	}
	if (j > 0)
	{
		num + 1 < board[i][j - 1] ? board[i][j - 1] = num + 1 : 0;
		get_distances(filler, board, i, j - 1, num + 1);
	}
	if (j < filler->n - 1)
	{
		num + 1 < board[i][j + 1] ? board[i][j + 1] = num + 1 : 0;
		get_distances(filler, board, i, j + 1, num + 1);
	}
}

void		make_board(t_filler *filler)
{
	int i;
	int j;
	int board[filler->m][filler->n];

	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == '.')
				board[i][j] = BIG_NUMBER;
			else
				board[i][j] = 0;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (board[i][j] == 0)
				get_distances(filler, board, i, j, 0);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
			ft_printf("%d ", board[i][j++]);
		ft_putendl("");
		i++;
	}
}

static void get_piece(char *line, t_filler *filler)
{
	int i;
	int j;

	get_next_line(1, &line);
	if (ft_strnequ(line, "Piece", 5) == 0)
		return ;
	if (*(line + 6) >= '0' && *(line + 6) <= '9')
		if ((filler->piece->y = ft_atoi(line + 6)) <= 0)
			return ;
	if (*(line + 7 + ft_count_digits_base(filler->piece->y, 10)) >= '0' && 
		*(line + 7 + ft_count_digits_base(filler->piece->y, 10)) <= '9')
		if ((filler->piece->x = ft_atoi(line + 7 +
			ft_count_digits_base(filler->piece->y, 10))) <= 0)
		{
			filler->piece->y = 0;
			return ;
		}
	filler->piece->piece = (char **)malloc(sizeof(char *) * filler->piece->y);
	i = 0;
	ft_strdel(&line);
	while (i < filler->piece->y)
	{
		get_next_line(1, &line); //error handle
		filler->piece->piece[i++] = ft_strdup(line);
		ft_strdel(&line);
	}
}

static void	get_map(char *line, t_filler *filler)
{
	int i;
	int j;
	int k;

	j = 0;
	filler->map = (char **)malloc(sizeof(char *) * filler->m);
	while (j < filler->m)
	{
		i = 0;
		k = 0;
		get_next_line(1, &line); //error handle
		while(*(line + i) >= '0' && *(line + i) <= '9')
			i++;
		i++;
		filler->map[j++] = ft_strdup(line + i);
		ft_strdel(&line);
	}
}

static int	get_plateau(char *line, t_filler *filler)
{
	int i;

	i = 0;
	get_next_line(1, &line);
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

static void	check_name(char *line, t_filler *filler)
{
	int i;

	i = 0;
	if (ft_strncmp("$$$ exec ", line, 9) != 0 || *(line + 9) != 'p')
		exit_func("Bad player info");
	while(*(line + 10 + i) == ' ')
		i++;
	if (ft_atoi(line + 10 + i) == 1)
		filler->playermark = 'O';
	else if (ft_atoi(line + 10 + i) == 2)
		filler->playermark = 'X';
	else
		exit_func("Bad player info");
	i++;
	while(*(line + 10 + i) == ' ')
		i++;
	if (*(line + 10 + i++) != ':')
		exit_func("Bad player info");
	while(*(line + 10 + i) == ' ')
		i++;
	if (ft_strstr(line + 10 + i, "aroi.filler") != NULL)
		exit_func("Bad player info");
}

void		find_place(t_filler *filler)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < filler->m)
	{
		if (ft_strchr(filler->map[i], filler->playermark))
			break;
		i++;
	}
	if (i != filler->m)
	{
		// while (filler->map[i][j] != filler->playermark)
		// 	j++;
		make_board(filler);
	}
	else
		ft_printf("0 0\n");
}

int			main(void)
{
	char		*line;
	t_filler	*filler;

	line = NULL;
	filler = ft_create_filler();
	if (get_next_line(1, &line) != 1 || line == NULL)
		exit_func("Bad player info (err 1)");
	check_name(line, filler);
	ft_strdel(&line);
	while (1)
	{
		if (get_plateau(line, filler) == 0)
			break;
		get_next_line(1, &line);		//get the line with 01234... etc
		ft_strdel(&line);
		get_map(line, filler);			// malloced map
		get_piece(line, filler);
		find_place(filler);
	}
	// int i = 0;
	// while (i < filler->m)
	// {
	// // int j = 0;
	// // 	while (j < filler->n)
	// // 	{
	// // 		ft_printf("%2d", filler->map[i][j]);
	// // 		j == filler->n - 1 ? write(1, "\n", 1) : 0;
	// // 		j++;
	// // 	}
	// 	ft_printf("%s\n", filler->map[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < filler->piece->y)
	// {
	// // int j = 0;
	// // 	while (j < filler->n)
	// // 	{
	// // 		ft_printf("%2d", filler->map[i][j]);
	// // 		j == filler->n - 1 ? write(1, "\n", 1) : 0;
	// // 		j++;
	// // 	}
	// 	ft_printf("%s\n", filler->piece->piece[i]);
	// 	i++;
	// }
	// system("leaks aroi.filler");
	return (0);
}
