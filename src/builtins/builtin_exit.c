/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/18 14:09:00 by yberramd         ###   ########.fr       */
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

extern int				g_retval;
extern char				*g_bgpid;
extern struct s_svar	*g_svar;
extern struct s_pos		*g_pos;
extern t_job			g_curjob;

static void		ft_free_shvar(void)
{
	struct s_svar	*tmp1;
	struct s_pos	*tmp2;

	while (g_svar)
	{
		tmp1 = g_svar->next;
		ft_strdel(&(g_svar->str));
		ft_strdel(&(g_svar->key));
		ft_strdel(&(g_svar->value));
		free(g_svar);
		g_svar = tmp1;
	}
	while (g_pos)
	{
		tmp2 = g_pos->next;
		ft_strdel(&(g_pos->str));
		ft_strdel(&(g_pos->key));
		ft_strdel(&(g_pos->value));
		free(g_pos);
		g_pos = tmp2;
	}
}

int				ft_clean_exit(char **av, int exit_status)
{
	extern char		**environ;

	if ((av) && ft_free_jcont(STOP_CHECK))
	{
		ft_dprintf(STDERR_FILENO, "There are stopped jobs.\n");
		return (1);
	}
	else if (!(av))
		ft_free_jcont(NO_CHECK);
	history(DELETE, NULL, NULL);
	ft_free_shvar();
	ft_tabdel(&av);
	ft_tabdel(&environ);
	ft_free_bintable();
	set_termcaps(TC_RESTORE);
	ft_strdel(&g_bgpid);
	ft_strdel(&g_curjob.cmd);
	exit(exit_status);
}

int				cmd_exit(int ac, char **av)
{
	int		exit_status;
	int		i;

	exit_status = (unsigned char)g_retval;
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
