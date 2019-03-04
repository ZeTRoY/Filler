/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:39:40 by aroi              #+#    #+#             */
/*   Updated: 2019/03/04 15:06:16 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static void		usage(void)
{
	ft_printf("%sUsage:%s ./visualizer -p1=`emoji` ", USAGE_BG, DEFAULT_BG);
	ft_putstr("-p2=`emoji` -empty=`emoji` -h --fast --very-fast --slow ");
	ft_putendl("--very-slow --nosound --chomp-1 --chomp-2 --help\n");
	ft_printf("%sAvailable emojies:%s\n\t%s ", AVLBL_BG, DEFAULT_BG, TURTLE);
	ft_printf("%sturle%s\n\t%s ", TURTLE_CLR, DEFAULT_FG, CRAB_INVADER);
	ft_printf("%salien%s\n\t%s %s", ALIEN_CLR, DEFAULT_FG, LANTERN, LNTRN_CLR);
	ft_printf("lantern%s\n\t%s %srocket", DEFAULT_FG, ROCKET, ROCKET_CLR);
	ft_printf("%s\n\t%s %smushroom", DEFAULT_FG, MUSHROOM, MUSHROOM_CLR);
	ft_printf("%s\n\t%s %spoliceman", DEFAULT_FG, POLICEMAN, POLICEMAN_CLR);
	ft_printf("%s\n\t%s %sogre%s\n", DEFAULT_FG, JP_OGRE, OGRE_CLR, DEFAULT_FG);
	ft_printf("\n%sOptions:%s\n-h, --help\n\toutput ", USAGE_BG, DEFAULT_BG);
	ft_putendl("usage of visualizer\n--fast\n\tlaunch visualizer in fast mode");
	ft_putendl("--very-fast\n\tlaunch visualizer in a very fast mode :D");
	ft_putstr("--slow\n\tlaunch visualizer in slow mode\n--very-slow");
	ft_putendl("\n\tlaunch visualizer in a very slow mode:ResidentSleeper:");
	ft_putendl("--nosound\n\tlaunch visualizer with no sounds");
	ft_putstr("--chomp1, --chomp2\n\tlaunch visualizer with default sound of ");
	ft_putstr("fitting a piece as sound chomp_1.mp3, chomp_2.wav ");
	ft_printf("\nrespectively\n%sExample:%s\n", USAGE_BG, DEFAULT_BG);
	ft_putendl("./visualizer -p1=policeman --slow --nosound\n");
	ft_putendl("Note: you can launch visualizer with no options at all! :)");
}

static char		*set_mark(char *str, char *prv_str)
{
	if (ft_strequ(str, "turtle"))
		return (TURTLE);
	else if (ft_strequ(str, "alien"))
		return (CRAB_INVADER);
	else if (ft_strequ(str, "lantern"))
		return (LANTERN);
	else if (ft_strequ(str, "rocket"))
		return (ROCKET);
	else if (ft_strequ(str, "mushroom"))
		return (MUSHROOM);
	else if (ft_strequ(str, "policeman"))
		return (POLICEMAN);
	else if (ft_strstr(str, "ogre"))
		return (JP_OGRE);
	else
		return (prv_str);
}

static int		get_options(char *str, t_visual *vis)
{
	if (ft_strnequ(str, "p1=", 3))
		vis->options.p1 = set_mark(str + 3, vis->options.p1);
	else if (ft_strnequ(str, "p2=", 3))
		vis->options.p2 = set_mark(str + 3, vis->options.p2);
	else if (ft_strnequ(str, "empty=", 6))
		vis->options.empty = set_mark(str + 6, vis->options.empty);
	else
		return (1);
	return (0);
}

static int		get_words(char *str, t_visual *vis)
{
	if (ft_strequ(str, "fast"))
		vis->options.speed = 1000;
	else if (ft_strequ(str, "very-fast"))
		vis->options.speed = 0;
	else if (ft_strequ(str, "slow"))
		vis->options.speed = 500000;
	else if (ft_strequ(str, "very-slow"))
		vis->options.speed = 1000000;
	else if (ft_strequ(str, "nosound"))
		vis->options.sound = 0;
	else if (ft_strequ(str, "chomp-1"))
		vis->options.sound = 1;
	else if (ft_strequ(str, "chomp-2"))
		vis->options.sound = 2;
	else if (ft_strequ(str, "help"))
		return (1);
	else
	{
		vis->options.speed = 50000;
		return (1);
	}
	return (0);
}

void			ft_parse_options(int argc, char **argv, t_visual *vis)
{
	int			i;
	int			usage_mark;

	i = 0;
	usage_mark = 0;
	vis->options.p1 = TURTLE;
	vis->options.p2 = CRAB_INVADER;
	vis->options.empty = MUSHROOM;
	vis->options.sound = 1;
	vis->options.speed = 50000;
	while (++i < argc && argv[i][0] == '-')
	{
		if (argv[i][1] != '-')
			get_options(argv[i] + 1, vis) ? usage_mark++ : 0;
		else
			get_words(argv[i] + 2, vis) ? usage_mark++ : 0;
	}
	if (usage_mark)
		usage();
}
