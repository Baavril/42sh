/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 21:06:23 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/29 16:18:00 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

static int	malloc_option(int ind[2], int opt[2], char **argv, char **option)
{
	opt[1]++;
	if (argv[opt[1]] && ft_strisnbr(argv[opt[1]]))
	{
		if (!(option[opt[0] - 1] = ft_strdup(argv[opt[1]])))
			return (0);
	}
	else
		return (argv[ind[0]][ind[1] - 1]);
	opt[0]++;
	return (-1);
}

static int	ft_bazar(int ind[2], char **argv, int opt)
{
	if (opt == 63)
	{
		ft_dprintf(2, "42sh: fc: -%c: invalid option\n", argv[ind[0]][ind[1]]);
		ind[1] = 1;
		ind[0] = 1;
	}
	else if (opt == 1)
	{
		ind[1] = 1;
		ind[0]++;
	}
	else if (opt == -1)
	{
		ind[1] = 1;
		ind[0] = 1;
	}
	return (opt);
}

int			ft_parser(int argc, char **argv, char *optstring, char **option)
{
	static int	ind[2] = {1, 1};
	char		*tmp;
	int			opt[2];
	int			ret;

	opt[0] = 1;
	if (argc > 1 && argc > ind[0])
	{
		if (argv[ind[0]][0] == '-' && argv[ind[0]][ind[1]] != '\0'
				&& !ft_strisnbr(argv[ind[0]]))
		{
			if (!(tmp = ft_strchr(optstring, argv[ind[0]][ind[1]])))
				return (ft_bazar(ind, argv, 63));
			ind[1]++;
			opt[1] = ind[0];
			while (tmp[opt[0]] == ':')
				if ((ret = malloc_option(ind, opt, argv, option)) != -1)
					return (ret);
			return (argv[ind[0]][ind[1] - 1]);
		}
		if (argv[ind[0]][0] != '-' && !ft_strisnbr(argv[ind[0]]))
			return (63);
		return (ft_bazar(ind, NULL, 1));
	}
	return (ft_bazar(ind, NULL, -1));
}
