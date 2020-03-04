/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unalias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:12:27 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/13 19:15:49 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "job.h"
#include "libft.h"
#include "error.h"
#include "builtins.h"
#include "ft_getopt.h"
#include "hash_module.h"
#include "htable_type_dispatcher.h"

/*
**     Unalias Errors:
** .no_arg(code 2): usage. "unalias: usage: unalias [-a] name [name ...]"
** .not found(code 1): the alias-name is not associated with an alias
*/

extern t_htable	*g_alias;
extern int		g_optind;
extern int		g_opterr;
extern int		g_optopt;

static int		ft_unalias_args(int ac, char **av)
{
	int		ret;
	int		i;

	ret = 0;
	i = g_optind;
	while (i < ac)
	{
		if (!g_alias || !ft_del_entry(g_alias, av[i]))
		{
			ft_dprintf(STDERR_FILENO,
					"%s: unalias: %s: not found.\n", g_progname, av[i]);
			ret = 1;
		}
		i++;
	}
	return (ret);
}

static int		ft_parse_unalias_opt(int ac, char **av)
{
	int		opt_a;
	int		ret;

	opt_a = 0;
	g_opterr = 0;
	g_optind = 1;
	while ((ret = ft_getopt(ac, av, "a")) > 0)
	{
		if (ret == '?')
		{
			ft_dprintf(STDERR_FILENO,
				"%s: unalias: -%c: invalid option.\n", g_progname, g_optopt);
			return (2);
		}
		if (ret == 'a')
			opt_a = 1;
	}
	return (opt_a);
}

int				cmd_unalias(int ac, char **av)
{
	int			ret;

	if ((ret = ft_parse_unalias_opt(ac, av)) == 1 || ac > 1)
	{
		if (g_alias)
			ft_empty_htable(g_alias);
		return (0);
	}
	if (ac < 2 || ret == 2)
	{
		ft_dprintf(STDERR_FILENO,
				"unalias: usage: unalias [-a] name [name ...].\n");
		return (2);
	}
	return (ft_unalias_args(ac, av));
}
