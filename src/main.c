/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:37:58 by aroi              #+#    #+#             */
/*   Updated: 2019/02/21 20:05:40 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	exit_func(char *str)
{
	ft_putendl(str);
	exit (1);
}

void		get_distances(t_filler *filler, char player, int i, int j)
{
// 	filler->board[i][j].sought = 1;
// 	if (i > 0 && filler->board[i - 1][j].sought == 0)
// 	{
// 		num + 1 < filler->board[i - 1][j].distance ? filler->board[i - 1][j].distance = num + 1 : 0;
// 		get_distances(filler, i - 1, j, num + 1);
// 	}
// 	if (i < filler->m - 1 && filler->board[i + 1][j].sought == 0)
// 	{
// 		num + 1 < filler->board[i + 1][j].distance ? filler->board[i + 1][j].distance = num + 1 : 0;
// 		get_distances(filler, i + 1, j, num + 1);
// 	}
// 	if (j > 0 && filler->board[i][j - 1].sought == 0)
// 	{
// 		num + 1 < filler->board[i][j - 1].distance ? filler->board[i][j - 1].distance = num + 1 : 0;
// 		get_distances(filler, i, j - 1, num + 1);
// 	}
// 	if (j < filler->n - 1 && filler->board[i][j + 1].sought == 0)
// 	{
// 		num + 1 < filler->board[i][j + 1].distance ? filler->board[i][j + 1].distance = num + 1 : 0;
// 		get_distances(filler, i, j + 1, num + 1);
// 	}
// 	filler->board[i][j].sought = 0;
	int x;
	int y;

	x = 0;
	while (x < filler->m)
	{
		y = -1;
		while (++y < filler->n)
		{
			if (player == 'a')
			{
				if (filler->board[x][y].aroi > ABS(x - i) + ABS(y - j))
					filler->board[x][y].aroi = ABS(x - i) + ABS(y - j);
			}
			else
			{
				if (filler->board[x][y].opponent > ABS(x - i) + ABS(y - j))
					filler->board[x][y].opponent = ABS(x - i) + ABS(y - j);
			}
			
		}
		x++;
	}
}

void		func_2(t_filler *filler, int xb, int yb, int xs, int ys)
{
	int i;
	int j;
	int	sum;

	sum = 0;
	i = 0;
	// ft_printf("xb - xp: %d, yb - yp: %d\n", xb - xs, yb - ys);

	// while (i < filler->piece->coord[0])
	// {
	// 	j = 0;
	// 	while (j < filler->piece->coord[1])
	// 	{
	// 		if (filler->piece->piece[i][j] == '*')
	// 		{
	// 			if (filler->map[xb - xp + i][yb - yp + j] != filler->playermark)
	// 				return ;
	// 			sum += filler->board[xb - xp + i][yb - yp + j].aroi + filler->board[xb - xp + i][yb - yp + j].opponent;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// if (sum < filler->sum)
	// {
	// 	filler->sum = sum;
	// 	filler->coord[0] = xb - xp;
	// 	filler->coord[1] = yb - yp;
	// }

	while (i <= filler->shape->coord[1][0] - filler->shape->coord[0][0])
	{
		j = 0;
		while (j <= filler->shape->coord[1][1] - filler->shape->coord[0][1])
		{
			if (filler->shape->shape[i][j] == '*')
			{
				if (filler->map[xb - xs + i][yb - ys + j] != filler->playermark && filler->map[xb - xs + i][yb - ys + j] != '.')
				{
					// write(1, "kronos\n", 7); //sad
					return ;
				}
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
	ft_printf("sum: %d\n", filler->sum);
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
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == filler->playermark && ft_check_piece(filler, i, j, xshape, yshape)) //ft_check_piece
			{
				func_2(filler, i, j, xshape, yshape);
				// ft_printf("| i: %d j: %d ", i - xshape, j - yshape);
			}
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
	//add distances for aroi
	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] == filler->playermark)
				get_distances(filler, 'a', i, j);
			j++;
		}
		i++;
	}
	//add distances for oppponent
	i = 0;
	while (i < filler->m)
	{
		j = 0;
		while (j < filler->n)
		{
			if (filler->map[i][j] != '.' && filler->map[i][j] != filler->playermark)
				get_distances(filler, 0, i, j);
			j++;
		}
		i++;
	}
	//place piece
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

	//								printing
	// i = 0;
	// while (i < filler->m)
	// {
	// 	j = 0;
	// 	while (j < filler->n)
	// 	{
	// 		ft_printf("%3d ", filler->board[i][j].aroi + filler->board[i][j].opponent);
	// 		j++;
	// 	}
	// 	ft_putendl("");
	// 	i++;
	// }
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
		filler->shape->shape[i] = ft_strsub(filler->piece->piece[i],
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
	while (++i < filler->piece->coord[1])
	{
		get_next_line(1, &line); //error handle
		filler->piece->piece[i] = ft_strdup(line);
		ft_strdel(&line);
		j = -1;
		while (++j < filler->piece->coord[0])
		{
			if (filler->piece->piece[i][j] == '*')
			{
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

	get_next_line(1, &line);
	if (ft_strnequ(line, "Piece", 5) == 0)
		return ;
	if (*(line + 6) >= '0' && *(line + 6) <= '9')
		if ((filler->piece->coord[1] = ft_atoi(line + 6)) <= 0)
			return ;
	if (*(line + 7 + ft_count_digits_base(filler->piece->coord[1], 10)) >= '0' && 
		*(line + 7 + ft_count_digits_base(filler->piece->coord[1], 10)) <= '9')
		if ((filler->piece->coord[0] = ft_atoi(line + 7 +
			ft_count_digits_base(filler->piece->coord[1], 10))) <= 0)
		{
			filler->piece->coord[1] = 0;
			return ;
		}
	filler->piece->piece = (char **)malloc(sizeof(char *) * filler->piece->coord[1]);
	ft_strdel(&line);
	filler->shape->coord[0][0] = filler->piece->coord[0];
	filler->shape->coord[0][1] = filler->piece->coord[1];
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
		get_next_line(1, &line); //error handle
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
		filler->coord[0] -= filler->shape->coord[0][0];
		filler->coord[1] -= filler->shape->coord[0][1];
		ft_printf("%d %d\n", filler->coord[0], filler->coord[1]);
		ft_refresh_filler(filler);
	}
	int i = 0;
	// while (i < filler->m)
	// {
	// int j = 0;
	// 	while (j < filler->n)
	// 	{
	// 		ft_printf("%2d", filler->map[i][j]);
	// 		j == filler->n - 1 ? write(1, "\n", 1) : 0;
	// 		j++;
	// 	}
	// 	ft_printf("%s\n", filler->map[i]);
	// 	i++;
	// }
	// int i = 0;
	// while (i < filler->piece->coord[1])
	// {
	// int j = 0;
	// 	while (j < filler->n)
	// 	{
	// 		ft_printf("%2d", filler->map[i][j]);
	// 		j == filler->n - 1 ? write(1, "\n", 1) : 0;
	// 		j++;
	// 	}
	// 	ft_printf("%s\n", filler->piece->piece[i]);
	// 	i++;
	// }

	// int i = 0;
	// while (filler->shape->shape[i])
	// 	ft_printf("%s\n", filler->shape->shape[i++]);
	// system("leaks aroi.filler");
	return (0);
}
