/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:37:58 by aroi              #+#    #+#             */
/*   Updated: 2019/02/25 17:43:30 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

# include <fcntl.h> //del

static void	exit_func(char *str)
{
	ft_putendl(str);
	exit (1);
}

void		get_distances(t_filler *filler, char player, int i, int j)
{
	int x;
	int y;

	x = 0;
	while (x < filler->m)
	{
		y = 0;
		while (y < filler->n)
		{
			if (player == filler->aroi)
			{
				if (filler->board[x][y].aroi > ABS(x - i) + ABS(y - j))
					filler->board[x][y].aroi = ABS(x - i) + ABS(y - j);
			}
			else
			{
				if (filler->board[x][y].opponent > ABS(x - i) + ABS(y - j))
					filler->board[x][y].opponent = ABS(x - i) + ABS(y - j);
			}
			y++;
		}
		x++;
	}
}

int		check_path(t_filler *filler, int xaroi)
{
	int i;

	i = 0;
	while (i < xaroi)
	{
		if (ft_tolower(filler->map[i][filler->n - 1]) == filler->opponent)
			return (0);
		i++;
	}
	return (1);
}

int		check_height(t_filler *filler, int *xaroi, int *xopp)
{
	int	i;

	i = 0;
	*xaroi = -1;
	*xopp = -1;
	while (i < filler->m)
	{
		if (*xaroi == -1 && ft_strchr(filler->map[i], filler->aroi))
			*xaroi = i;
		if (*xopp == -1 && (ft_strchr(filler->map[i], filler->opponent) ||
				ft_strchr(filler->map[i], ft_tolower(filler->opponent))))
			*xopp = i;
		if (*xaroi > -1 && *xopp > -1)
			break;
		i++;
	}
	if (*xaroi == -1)
		return (*xaroi);
	else if (*xaroi >= *xopp && *xaroi != 0)
		return (0);
	return (1);
}

void		func_2(t_filler *filler, int xb, int yb, int xs, int ys)
{
	int i;
	int j;
	int	placed;
	int	sum;

	sum = 0;
	i = 0;
	placed = 0;
	while (i <= filler->shape->coord[1][0] - filler->shape->coord[0][0])
	{
		j = 0;
		while (j <= filler->shape->coord[1][1] - filler->shape->coord[0][1])
		{
			if (filler->shape->shape[i][j] == '*')
			{
				if (ft_toupper((filler->map[xb - xs + i][yb - ys + j]) == filler->opponent)
					|| (filler->map[xb - xs + i][yb - ys + j] == filler->aroi
					&& placed))
					return ;
				if (filler->map[xb - xs + i][yb - ys + j] == filler->aroi)
					placed = 1;
				sum += filler->board[xb - xs + i][yb - ys + j].aroi + filler->board[xb - xs + i][yb - ys + j].opponent;
			}
			j++;
		}
		i++; 
	}
	if (filler->sum > sum)
	{
		filler->sum = sum;
		filler->coord[0] = xb - xs;
		filler->coord[1] = yb - ys;
	}
}

int		ft_check_piece(t_filler *filler, int xb, int yb, int xs, int ys)
{
	int		xlen;
	int		ylen;

	xlen = filler->shape->coord[1][0] - filler->shape->coord[0][0];
	ylen = filler->shape->coord[1][1] - filler->shape->coord[0][1];
	if (xb - xs < 0 ||
			yb - ys < 0 ||
				xb + xlen + 1 - xs > filler->m ||
					yb + ylen + 1 - ys > filler->n)
		return (0);
	return (1);
}

void		func_1(t_filler *filler, int xshape, int yshape)
{
	int i;
	int j;
	
	i = 0;
	// if (filler->place == 'h')
	// {
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == filler->aroi && ft_check_piece(filler, i, j, xshape, yshape)) //ft_check_piece
			{
				func_2(filler, i, j, xshape, yshape);
				// ft_printf("| i: %d j: %d ", i - xshape, j - yshape);
			}
			j++;
		}
		i++;
	}
	// }
	// else
	// {
	// 	i = filler->m;
	// 	while (i-- > 0)
	// 	{
	// 		j = 0;
	// 		while (j < filler->n)
	// 		{
	// 			if (filler->map[i][j] == filler->aroi && ft_check_piece(filler, i, j, xshape, yshape))
	// 				func_2(filler, i, j, xshape, yshape);
	// 			j++;
	// 		}
	// 	}
	// }
}

void		place_piece(t_filler *filler)
{
	int i;
	int j;

	// if (filler->place == 'h')
	// {
		i = -1;
		while (++i <= filler->shape->coord[1][0] - filler->shape->coord[0][0])
		{
			j = -1;
			while (++j <= filler->shape->coord[1][1] - filler->shape->coord[0][1])
			{
				if (filler->shape->shape[i][j] == '*')
					func_1(filler, i, j);
			}
		}
	// }
	// else
	// {
	// 	i = -1;
	// 	while (++i < filler->shape->coord[1][0] - filler->shape->coord[0][0] + 1)
	// 	{
	// 		// write(1, "wow\n", 4);
	// 		j = filler->shape->coord[1][1] - filler->shape->coord[0][1] + 1;
	// 		// ft_printf("%d %d %d\n", filler->shape->coord[1][1], filler->coord[0][1]);
	// 		while (j-- > 0)
	// 		{
	// 			if (filler->shape->shape[i][j] == '*')
	// 				func_1(filler, i, j);
	// 		}
	// 	}
	// }
}

void	get_distance_to_cell(t_filler *filler, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->board[i][j].aroi > ABS(x - i) + ABS(y - j))
				filler->board[i][j].aroi = ABS(x - i) + ABS(y - j);
			if (ft_toupper(filler->map[i][j]) == filler->opponent)
				get_distances(filler, filler->opponent, i, j);
			j++;
		}
		i++;
	}
}

void	get_distances_for_players(t_filler *filler)
{
	int i;
	int j;

	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == filler->aroi)
				get_distances(filler, filler->aroi, i, j);
			else if (ft_toupper(filler->map[i][j]) == filler->opponent)
				get_distances(filler, filler->opponent, i, j);
			j++;
		}
		i++;
	}
}

void		make_board(t_filler *filler)
{
	int i;
	int j;

	//make_board
	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == '.')
			{
				filler->board[i][j].aroi = BIG_NUMBER;
				filler->board[i][j].opponent = BIG_NUMBER;
			}
			else
			{
				filler->board[i][j].aroi = 0;
				filler->board[i][j].opponent = 0;
			}
			j++;
		}
		i++;
	}
}

void	cut_shape(t_filler *filler)
{
	int i;
	filler->shape->shape = (char **)malloc(sizeof(char *) *
		(filler->shape->coord[1][0] -
			filler->shape->coord[0][0] + 2));
	i = 0;
	while (i < filler->shape->coord[1][0] -
		filler->shape->coord[0][0] + 1)
	{
		filler->shape->shape[i] = ft_strsub(filler->piece->piece[i + filler->shape->coord[0][0]],
			filler->shape->coord[0][1], filler->shape->coord[1][1] -
				filler->shape->coord[0][1] + 1);
		i++;
	}
	filler->shape->shape[filler->shape->coord[1][0] -
		filler->shape->coord[0][0] + 1] = NULL;
}

void	func_3(t_filler *filler, char *line)
{
	int i;
	int j;

	i = -1;
	while (++i < filler->piece->len[1])
	{
		get_next_line(0, &line); //error handle
		filler->piece->piece[i] = ft_strdup(line);
		ft_strdel(&line);
		j = -1;
		while (++j < filler->piece->len[0])
		{
			if (filler->piece->piece[i][j] == '*')
			{
				// ft_printf("filler: %d j: %d\n", filler->shape->coord[0][1], j);
				i < filler->shape->coord[0][0] ?
					filler->shape->coord[0][0] = i : 0;
				j < filler->shape->coord[0][1] ?
					filler->shape->coord[0][1] = j : 0;
				i > filler->shape->coord[1][0] ?
					filler->shape->coord[1][0] = i : 0;
				j > filler->shape->coord[1][1] ?
					filler->shape->coord[1][1] = j : 0;
			}
		}
	}
	cut_shape(filler);
}

static void get_piece(char *line, t_filler *filler)
{
	int i;
	int j;

	get_next_line(0, &line);
	if (ft_strnequ(line, "Piece", 5) == 0)
		return ;
	if (*(line + 6) >= '0' && *(line + 6) <= '9')
		if ((filler->piece->len[1] = ft_atoi(line + 6)) <= 0)
			return ;
	if (*(line + 7 + ft_count_digits_base(filler->piece->len[1], 10)) >= '0' && 
		*(line + 7 + ft_count_digits_base(filler->piece->len[1], 10)) <= '9')
		if ((filler->piece->len[0] = ft_atoi(line + 7 +
			ft_count_digits_base(filler->piece->len[1], 10))) <= 0)
		{
			filler->piece->len[1] = 0;
			return ;
		}
	filler->piece->piece = (char **)malloc(sizeof(char *) * filler->piece->len[1]);
	ft_strdel(&line);
	// ft_printf("%d %d\n", filler->piece->len[0], filler->piece->len[1]);
	filler->shape->coord[0][0] = filler->piece->len[1];
	filler->shape->coord[0][1] = filler->piece->len[0];
	filler->shape->coord[1][0] = 0;
	filler->shape->coord[1][1] = 0;
	func_3(filler, line);
}

static void	get_map(char *line, t_filler *filler)
{
	int i;
	int j;

	i = 0;
	filler->map = (char **)malloc(sizeof(char *) * filler->m);
	filler->board = (t_board **)malloc(sizeof(t_board *) * filler->m);
	while (i < filler->m)
	{
		j = 0;
		get_next_line(0, &line); //error handle
		while(*(line + j) >= '0' && *(line + j) <= '9')
			j++;
		j++;
		filler->map[i] = ft_strdup(line + j);
		filler->board[i++] = (t_board *)malloc(sizeof(t_board) * filler->n);
		ft_strdel(&line);
	}
}

static int	get_plateau(char *line, t_filler *filler)
{
	int i;

	i = 0;
	get_next_line(0, &line);
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

void	skip_whitespaces(char *line, int *i)
{
	while (*(line + *i) == ' ')
		(*i)++;
}

static void	check_name(char *line, t_filler *filler)
{
	int i;

	i = 0;
	if (ft_strncmp("$$$ exec ", line, 9) != 0 || *(line + 9) != 'p')
		exit_func("Bad player info");
	skip_whitespaces(line + 10, &i);
	if (ft_atoi(line + 10 + i) == 1)
	{
		filler->aroi = 'O';
		filler->opponent = 'X';
	}
	else if (ft_atoi(line + 10 + i) == 2)
	{
		filler->aroi = 'X';
		filler->opponent = 'O';
	}
	else
		exit_func("Bad player info");
	i++;
	skip_whitespaces(line + 10, &i);
	if (*(line + 10 + i++) != ':')
		exit_func("Bad player info");
	skip_whitespaces(line + 10, &i);
	if (ft_strstr(line + 10 + i, "aroi.filler") == NULL)
		exit_func("Bad player info");
}

void		find_place(t_filler *filler)
{
	int i;
	int xaroi;
	int xopp;

	make_board(filler);
	i = check_height(filler, &xaroi, &xopp);
	if (i == -1)
		return ;
	if (filler->m < 20 || filler->n < 20)
	{
		if (i == 0)
		{
			if (check_path(filler, xaroi) == 1)
				get_distance_to_cell(filler, 0, filler->n - 1);
			else
				get_distance_to_cell(filler, filler->m - 1, 0);
		}
		else if (xaroi < xopp)
			get_distance_to_cell(filler, xopp - 1, 0);
		else
			get_distances_for_players(filler);
	}
	else
		get_distances_for_players(filler);
	place_piece(filler);
}

int			main(void)
{
	char		*line;
	t_filler	*filler;

	line = NULL;
	filler = ft_create_filler();
	if (get_next_line(0, &line) < 0 || line == NULL)
		exit_func("Bad player info (err 1)");
	check_name(line, filler);
	ft_strdel(&line);
	while (1)
	{
		if (get_plateau(line, filler) == 0)
			break;
		get_next_line(0, &line);
		ft_strdel(&line);
		get_map(line, filler);			// malloced map
		get_piece(line, filler);
		find_place(filler);
		ft_printf("%d %d\n", filler->coord[0] - filler->shape->coord[0][0],
			filler->coord[1] - filler->shape->coord[0][1]);
		ft_refresh_filler(filler);
	}
	system("leaks aroi.filler");
	return (0);
}
