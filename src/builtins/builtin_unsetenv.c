/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:25:19 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/29 13:49:23 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell_variables.h"
#include "hash_module.h"
#include "libft.h"

extern char	*g_progname;

int			cmd_unsetenv(int ac, char **av)
{
	int		i;

	i = 0;
	if (ac >= 2)
	{
		while (++i < ac)
		{
			if (ft_unsetenv(av[i]) == -1)
				ft_dprintf(STDERR_FILENO,
					"%s: unsetenv: %s: No such variable in environnement.\n",
											g_progname, av[i]);
			else
				unsetvarset(av[i]);
		}
		return (0);
	}
	else
		ft_dprintf(STDERR_FILENO,
					"%s: unsetenv: Too few arguments.\n",
												g_progname);
	return (1);
}
