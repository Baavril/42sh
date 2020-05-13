/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 12:09:54 by user42            #+#    #+#             */
/*   Updated: 2020/05/09 18:02:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"
#include "libft.h"

extern char	*g_progname;

static void	ft_printenv(void)
{
	extern char		**environ;

	ft_print_tables(environ);
}

int			cmd_setenv(int ac, char **av)
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
		return (0);
	}
	else
		ft_dprintf(STDERR_FILENO,
						"%s: unsetenv: %s: Too many arguments.",
												g_progname, av[1]);
	return (1);
}
