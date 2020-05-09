/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:25:19 by user42            #+#    #+#             */
/*   Updated: 2020/05/09 17:57:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

extern char	*g_progname;

int			cmd_unsetenv(int ac, char **av)
{
	if (ac >= 2)
	{
		if (ft_unsetenv(av[1]) == -1)
			ft_dprintf(STDERR_FILENO,
					"%s: unsetenv: %s: No such variable in environnement.\n",
												g_progname, av[1]);
		return (0);
	}
	if (ac < 2)
		ft_dprintf(STDERR_FILENO,
					"%s: unsetenv: %s: Too few arguments.",
												g_progname, av[1]);
	return (1);
}
