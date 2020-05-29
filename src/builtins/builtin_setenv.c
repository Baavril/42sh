/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 12:09:54 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/29 13:49:21 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hash_module.h"
#include "builtins.h"
#include "libft.h"

extern char			*g_progname;
extern t_htable		*g_bintable;

static void			ft_printenv(void)
{
	extern char		**environ;

	ft_print_tables(environ);
}

int					cmd_setenv(int ac, char **av)
{
	char	*value;

	value = "";
	if (ac == 1)
	{
		ft_printenv();
		return (0);
	}
	else if (ac < 4)
	{
		if (ac == 3)
			value = av[2];
		ft_setenv(av[1], value);
		if (!(ft_strcmp("PATH", av[1])) && (g_bintable))
			ft_empty_htable(g_bintable);
		return (0);
	}
	else
		ft_dprintf(STDERR_FILENO,
						"%s: setenv: Too many arguments.", g_progname);
	return (1);
}
