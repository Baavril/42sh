/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 21:06:23 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/14 21:07:42 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

int		ft_parser(int argc, char **argv, char *optstring, char **option)
{
	static int	ind = 1;
	static int	i = 1;
	char		*tmp;
	int			opt;
	int			argv_opt;

	opt = 1;
	if (argc > 1 && (argc - 1) >= ind)
	{
		while (argv[ind][0] == '-' && argv[ind][i] != '\0'
				&& !ft_strisnbr(argv[ind]))
		{
			if (!(tmp = ft_strchr(optstring, argv[ind][i])))
			{
				ft_dprintf(2, "42sh: fc: -%c: invalid option\n", argv[ind][i]);
				i = 1;
				ind = 1;
				return (63);
			}
			else
			{
				i++;
				argv_opt = ind;
				while (tmp[opt] == ':')
				{
					argv_opt++;
					if (argv[argv_opt] && ft_strisnbr(argv[argv_opt]))
					{
						if (!(option[opt - 1] = ft_strdup(argv[argv_opt])))
							return (0);
					}
					else
						return (argv[ind][i - 1]);
					opt++;
				}
				return (argv[ind][i - 1]);
			}
		}
		if (argv[ind][0] != '-' && !ft_strisnbr(argv[ind]))
			return (63);
		i = 1;
		ind++;
		return (1);
	}
	i = 1;
	ind = 1;
	return (-1);
}
