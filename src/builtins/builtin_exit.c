/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/18 14:59:18 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell_variables.h"
#include "termcaps.h"
#include "builtins.h"
#include "history.h"
#include "libft.h"
#include "error.h"
#include "jcont.h"

extern int		g_retval;
struct s_svar	*g_svar;

static int		ft_clean_exit(char **av, int exit_status)
{
	struct s_svar	*tmp;
	extern char		**environ;

	if (ft_free_jcont())
	{
		ft_dprintf(STDERR_FILENO, "There are stopped jobs.\n");
		return (1);
	}
	while (g_svar)
	{
		tmp = g_svar->next;
		ft_strdel(&(g_svar->str));
		ft_strdel(&(g_svar->key));
		ft_strdel(&(g_svar->value));
		free(g_svar);
		g_svar = tmp;
	}
	ft_tabdel(&av);
	ft_tabdel(&environ);
	history(DELETE, NULL, NULL);
	ft_free_bintable();
	set_termcaps(TC_RESTORE);
	system("leaks 42sh");
	exit(exit_status);
}

int				cmd_exit(int ac, char **av)
{
	int		exit_status;
	int		i;

	exit_status = (unsigned char)g_retval;
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (ac > 1)
	{
		i = (!ft_strcmp("--", av[1]) && ac > 2) ? 2 : 1;
		if (ft_isnumber(av[i]))
		{
			if (av[i + 1])
			{
				ft_dprintf(STDERR_FILENO,
						"%s: %s: too many arguments.\n", g_progname, av[0]);
				return (1);
			}
			exit_status = (unsigned char)ft_atoi(av[i]);
		}
		else if (ft_strcmp("--", av[1]) && (exit_status = 2))
			ft_dprintf(STDERR_FILENO,
						"%s: exit: %s: numeric argument required.\n",
						g_progname, av[i]);
	}
	return (ft_clean_exit(av, exit_status));
}
