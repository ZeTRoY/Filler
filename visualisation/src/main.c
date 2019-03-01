#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>

#include "visual.h"
#include "libft.h"
#include "get_next_line.h"
#include <locale.h>

/*void	failed(const char *str)
{
	perror(str);
	ExitProgram(EXIT_FAILURE);
}

static FILE *open_tty(char *path)
{
    FILE *fp;
#ifdef USE_XTERM_PTY
    int amaster;
    int aslave;
    char slave_name[1024];
    char s_option[sizeof(slave_name) + 80];
    const char *xterm_prog = 0;

	xterm_prog = "xterm";

    if (openpty(&amaster, &aslave, slave_name, 0, 0) != 0
	|| strlen(slave_name) > sizeof(slave_name) - 1)
    	failed("pty");
	if (strrchr(slave_name, '/') == 0)
	{
		errno = EISDIR;
		failed("slave_name"):
    }
    _nc_SPRINTF(s_option, _nc_SLIMIT(sizeof(s_option))
		"-S%s/%d", slave_name, aslave);
    if (fork()) {
	execlp(xterm_prog, xterm_prog, s_option, "-title", path, (char *) 0);
	_exit(0);
    }
    fp = fdopen(amaster, "r+");
    if (fp == 0)
	failed(path);
#else
    struct stat sb;

    if (stat(path, &sb) < 0)
	failed(path);
    if ((sb.st_mode & S_IFMT) != S_IFCHR) {
	errno = ENOTTY;
	failed(path);
    }
    fp = fopen(path, "r+");
    if (fp == 0)
	failed(path);
    printf("opened %s\n", path);
#endif
    assert(fp != 0);
    return fp;
}*/

// WINDOW *create_win()
WINDOW *create_win(int height, int width, int x, int y)
{
	WINDOW *win;
	
	win = newwin(height, width, x, y);
	box(win, 0, 0);
	return (win);
}

int		exit_func(char *str)
{
	endwin();
	ft_printf("%s\n", str);
	exit(1);
}

// void	resize(void)
// {
// 	struct winsize w;

// 	ioctl(0, TIOCGWINSZ, &w);
// 	g_vis.col = w.ws_col;
// 	g_vis.row = w.ws_row;
// }

// void	signal_handler(int sig)
// {
// 	if (sig == SIGWINCH)
// 		resize();
// }

char	**get_map(t_visual *vis, char **line)
{
	char **map;
	int i;
	int j;

	vis->m = ft_atoi(*line + 8);
	map = (char **)malloc(sizeof(char *) * (vis->m));
	vis->n = ft_atoi(*line + 8 + ft_count_digits_base(vis->m, 10) + 1);
	ft_strdel(line);
	get_next_line(STDIN_FILENO, line);
	i = -1;
	while (++i < vis->m)
	{
		j = 0;
		ft_strdel(line);
		get_next_line(STDIN_FILENO, line);
		while (*(*line + j) >= '0' && *(*line + j) <= '9')
			j++;
		map[i] = ft_strdup(*line + j + 1);
	}
	ft_strdel(line);
	return (map);
}

WINDOW	*get_score(t_visual *vis)
{
	int i;
	int j;
	char *str[3];

	WINDOW *win = create_win(vis->m + 2, 16, 0, vis->n * 2 + 10);
	j = -1;
		// if (j == 0)
			str[0] = "\xF0\x9F\x90\xA2";
		// else if (j == 1)
			str[1] = "\xF0\x9F\x90\x87";
		// else
			str[2] = "\xF0\x9F\x8F\xAE";
	// while (++j <= 3)
	// {
	// 	i = -1;
	// 	while (++i < vis->m)
	// 	{
	// 		mvwaddstr(win, i + 1, j * 5 + 2, str[j]);
	// 	}
	// }

	//first column
	i = -1;
	while (++i < vis->m * vis->filler.p1 / vis->m / vis->n)
	{
		mvwaddstr(win, vis->m - i, 2, str[0]);
	}
	i = -1;
	while (++i < vis->m * vis->filler.p2 / vis->m / vis->n)
	{
		mvwaddstr(win, vis->m - i, 7, str[1]);
	}
	i = -1;
	while (++i < vis->m * vis->filler.empty / vis->m / vis->n)
	{
		mvwaddstr(win, vis->m - i, 12, str[2]);
	}
	return (win);
}

WINDOW	*create_win3(t_visual *vis, int len)
{
	WINDOW	*win;
	int		n;

	n = 0;
	if (len + 8 > vis->n)
		n = len + 8 > vis->n + 5 ? vis->n - 9 - len / 2: vis->n - len / 2 - 4;
	n <= 0 ? n = vis->n - len / 2 - 4 : 0;
	n <= 0 ? n = vis->n : 0;
	win = create_win(3, len + 8 + 2, vis->m + 2, n);
	wattron(win, A_BOLD | COLOR_PAIR(3));
	return (win);
}

WINDOW	*show_winner(t_visual *vis)
{
	int		len;
	WINDOW	*win;

	if (vis->filler.p1 > vis->filler.p2)
	{
		len = ft_strlen(vis->p1_name);
		win = create_win3(vis, len);
		mvwaddstr(win, 1, 1, vis->p1_name);
	}
	else
	{
		len = ft_strlen(vis->p2_name);
		win = create_win3(vis, len);
		mvwaddstr(win, 1, 1, vis->p2_name);
	}
	mvwaddstr(win, 1, 1 + len, " wins!\xF0\x9F\x8E\x89");
	wattroff(win, A_BOLD | COLOR_PAIR(3));
	return (win);
}

WINDOW	*initialise_window(t_visual *vis)
{
	WINDOW *win;

	win = create_win(vis->m + 2, vis->n * 2 + 2, 0, 0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_YELLOW, COLOR_BLUE);
	return (win);
}

void	ft_resize()
{
	exit_func("finitalacomedia");
}

void	draw_map(t_visual *vis, char **map, WINDOW *win)
{
	int i;
	int j;
	int k1;
	int k2;
	int min;
	int col;
	int row;

	getmaxyx(stdscr, row, col);
	// if (col / vis->m < 1 || row / vis->n < 1)
	// 	ft_resize();
	// else
	// 	min = col / vis->m > row / vis->n ? row / vis->n : col / vis->m;
	i = -1;
	while (++i < vis->m)
	{
		// k2 = -1;
		// while (++k2 < min)
		// {
			j = -1;
			while (++j < vis->n)
			{
				// k1 = -1;
				// while (++k1 < min)
				// {
					if (map[i][j] == '.')
					{
						// waddch(win, '.');
						// waddch(win, ACS_);
						mvwaddstr(win, i + 1, j * 2 + 1, "\xF0\x9F\x8F\xAE");//mushroom - \xF0\x9F\x8D\x84 : bento - \xF0\x9F\x8D\xB1 : red lantern - \xF0\x9F\x8F\xAE
						vis->filler.empty++;
					}
					else if (map[i][j] == 'o' || map[i][j] == 'O')
					// 	waddstr(win, "o");
					{
						if (map[i][j] == 'o')
							wattron(win, COLOR_PAIR(1));
						mvwaddstr(win, i + 1, j * 2 + 1, "\xF0\x9F\x90\xA2");
						vis->filler.p1++;
						wattroff(win, COLOR_PAIR(1));
					}
					else
					{
					// 	waddstr(win, "x");
						if (map[i][j] == 'x')
							wattron(win, COLOR_PAIR(2));
						mvwaddstr(win, i + 1, j * 2 + 1, "\xF0\x9F\x90\x87");
						vis->filler.p2++;
						wattroff(win, COLOR_PAIR(2));
					}
				// }
			}
			// waddch(win, '\n');
		}
	// }
}

void	resize(int sig)
{
	exit_func("{red}Please, don't resize terminal emulator!{eoc}");
}

void	refresh_filler(t_visual *vis)
{
	vis->filler.empty = 0;
	vis->filler.p1 = 0;
	vis->filler.p2 = 0;
}

void	end_visual(WINDOW *win3)
{
	delwin(win3);
	endwin();
}

void	get_and_write(WINDOW *win, t_visual vis)
{
	char *line;
	char **map;
	WINDOW *win2;
	WINDOW *win3;

	if (!initscr())
		exit_func("Screen initialisation problem.");
	curs_set(0);
	cbreak();
	noecho();
	line = NULL;
	if (get_next_line(STDIN_FILENO, &line) < 0 || !line)
		exit_func("Bad map input (0)");
	while (1)
	{
		signal(SIGWINCH, resize);
		if (ft_strstr(line, "Plateau"))
		{
			refresh_filler(&vis);
			map = get_map(&vis, &line);
			win = initialise_window(&vis);
			draw_map(&vis, map, win);
			win2 = get_score(&vis);
			wrefresh(win);
			wrefresh(win2);
			usleep(10000);
			delwin(win);
			delwin(win2);
		}
		ft_strdel(&line);
		if (get_next_line(STDIN_FILENO, &line) == 0)
			break;
		// if (get_next_line(STDIN_FILENO, &line) < 0 || !line)
			// exit_func("Bad map input (0)");
	}
	win3 = show_winner(&vis);
	wrefresh(win3);
	int wg;
	while ((wg = wgetch(win3)) != ESC_KEY)
	{
		continue;
	}
	
	end_visual(win3);
}

char	*get_name_of_player(char *player)
{
	char *line;
	char *tmp;
	char *name;

	if (get_next_line(STDIN_FILENO, &line) < 0 || line == NULL)
		exit_func("Bad name input (1)");
	while (ft_strstr(line, "$$$ exec") == NULL || ft_strstr(line, player) == NULL)
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

void	get_names(t_visual *vis)
{
	vis->p1_name = get_name_of_player("p1");
	vis->p2_name = get_name_of_player("p2");
}

int main(void)
{
	WINDOW *win;
	char **map;
	t_visual vis;

	setlocale(LC_ALL, "");
	get_names(&vis);
	// if (!(initscr()))
	// 	exit_func("Error on initialising ncurses");
	// win = create_win(50, 50, 0, 0);
	get_and_write(win, vis);
	// wgetch(win);
	// delwin(win);
	// endwin();
/*
	//system("osascript script");
	
	//int opened = open("/dev/ttys001", O_RDWR);
	FILE *op = fopen("/dev/ttys001", "rw+");
	SCREEN *screen = newterm(NULL, op, op);
	SCREEN *screen2 = set_term(screen);
	getch();
	system("clear");
	printw("hello!\n");
	//printw("Max loh!\n");
	refresh();
	getch();
	//refresh();
	endwin();
	delscreen(screen2);
	delscreen(screen);*/
	return (0);
}
