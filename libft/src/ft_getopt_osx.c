/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_osx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:47:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:47:08 by abarthel         ###   ########.fr       */
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
	++g_optind;
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

static int	parse_optstring(int argc, char *const *argv, const char *optstring)
{
	static int	index;
	static int	i = 1;
	int			ret;

	ret = 0;
	if (!g_optind)
	{
		i = 1;
		return (0);
	}
	if (g_optarg || index > g_optind)
	{
		i = 1;
		g_optarg = NULL;
	}
	index = g_optind;
	ret = parse_char(argc, argv, &argv[g_optind][i], optstring);
	++i;
	if (argv[g_optind] && !argv[g_optind][i])
	{
		i = 1;
		if (!g_optarg)
			++g_optind;
	}
	return (ret);
}

int			ft_getopt(int argc, char *const argv[], const char *optstring)
{
	int		ret;

	ret = 0;
	if (!optstring || g_optind >= argc || !argv[g_optind]
			|| *(argv[g_optind]) != '-' || !ft_strcmp((argv[g_optind]), "-"))
		return (-1);
	else if (!ft_strcmp((argv[g_optind]), "--"))
	{
		g_optopt = *argv[g_optind];
		++g_optind;
		return (-1);
	}
	else if (argv[g_optind] && *(argv[g_optind]))
	{
		g_optarg = NULL;
		g_optopt = 0;
		ret = parse_optstring(argc, argv, optstring);
	}
	if (!g_optopt)
		g_optopt = ret;
	return (ret);
}

#endif
