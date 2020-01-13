/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_osx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:47:26 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/13 18:28:45 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_getopt.h"

char	*g_optarg = NULL;
int		g_optind = 1;
int		g_opterr = 1;
int		g_optopt;

#ifndef __unix__

static int	parse_char_mod(int argc, char *const *argv, char *c,
		const char *optstring)
{
	if (!c[1])
	{
		++g_optind;
		if (g_optind < argc)
			g_optarg = argv[g_optind];
		else
		{
			g_optopt = *c;
			--g_optind;
			if (*optstring == ':')
				return (':');
			else
			{
				if (g_opterr)
					ft_dprintf(STDERR_FILENO,
						"%s: option requires an argument -- %c\n", argv[0], *c);
				return ('?');
			}
		}
	}
	else
		g_optarg = &c[1];
	return (0);
}

static int	parse_char(int argc, char *const *argv, char *c,
		const char *optstring)
{
	int i;
	int tmp;

	i = 0;
	while (optstring[i])
	{
		if (optstring[i] == ':')
		{
			++i;
			continue ;
		}
		if (*c == optstring[i])
		{
			if (optstring[i + 1] == ':')
				if ((tmp = parse_char_mod(argc, argv, c, optstring)))
					return (tmp);
			return (*c);
		}
		else
			++i;
	}
	g_optopt = *c;
	if (g_opterr && *optstring != ':')
		ft_dprintf(STDERR_FILENO, "%s: illegal option -- %c\n", argv[0], *c);
	return ('?');
}

int		ft_getopt(int ac, char *const av[], const char *optstring)
{
	int				ret;
	static char		*optarg = NULL;
	static char		*opt = NULL;

	ret = 0;
	if (!optstring || g_optind < 0 || g_optind > ac)
		return (-1);
	if (!optarg || !opt || !(*opt) || g_optind == 1 || g_optarg)
	{
		if (!av[g_optind] || *av[g_optind] != '-' || !ft_strcmp(av[g_optind], "-"))
			return (-1);
		optarg = av[g_optind++];
		if (!ft_strcmp(optarg, "--"))
		{
			g_optopt = '-';
			return (-1);
		}
		opt = optarg + 1;
	}
	g_optarg = NULL;
	g_optopt = 0;
	ret = parse_char(ac, av, opt++, optstring);
	if (!g_optopt)
		g_optopt = ret;
	return (ret);
}

#endif
