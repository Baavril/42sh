/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 12:42:49 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/17 19:26:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "sig_handler.h"
#include "parser.h"
#include "error.h"
#include "libft.h"

extern char		*g_progname;

static int		ft_env_exec(char *to_exec, char **av)
{
	extern char	**environ;
	int			father;
	int			status;

	status = 0;
	father = fork();
	if (father == 0)
	{
		set_signals(CHILD);
		execve(to_exec, av, environ);
	}
	else if (father > 0)
	{
		setpgid(father, father);
		tcsetpgrp(STDIN_FILENO, father);
		wait(&status);
		tcsetpgrp(STDIN_FILENO, getpid());
	}
	ft_setenv("_", av[0]);
	ft_strdel(&to_exec);
	return (status);
}

static int		ft_set_tmp_var(char **av)
{
	char		*eq;

	if (!(ft_strcmp(av[0], "-u")) && (av[1]))
	{
		ft_unsetenv(av[1]);
		return (2);
	}
	if (!(ft_strcmp(av[0], "-P")) && (av[1]))
	{
		ft_setenv("PATH", av[1]);
		return (2);
	}
	eq = ft_strchr(av[0], '=');
	*(eq++) = '\0';
	ft_setenv(av[0], eq);
	*(--eq) = '=';
	return (1);
}

static int		ft_construct_tmp_env(char **av, int cmd)
{
	extern char **environ;
	int			i;

	i = 1;
	if ((av[i]) && !(ft_strcmp(av[i], "-i")))
	{
		if (!(environ = (char**)malloc(sizeof(char*))))
		{
			psherror(e_cannot_allocate_memory, NULL, e_invalid_type);
			return (1);
		}
		environ[0] = NULL;
		i++;
	}
	else
		environ = ft_tabcpy(environ);
	while (i < cmd)
		i += ft_set_tmp_var(&(av[i]));
	return (0);
}

static int		ft_cmd_start(char **av)
{
	int		i;

	i = 1;
	if ((av[i]) && !(ft_strcmp(av[i], "-i")))
		i++;
	while (av[i])
	{
		if ((!(ft_strcmp(av[i], "-u")) && (av[i + 1]))
		|| (!(ft_strcmp(av[i], "-P")) && (av[i + 1])))
			i += 2;
		else if (ft_strchr(av[i], '='))
			i++;
		else
			break ;
	}
	return (i);
}

int				cmd_env(int ac, char **av)
{
	extern char **environ;
	char		**save_env;
	char		*to_exec;
	int			i;

	save_env = environ;
	if ((i = ft_cmd_start(av)) < ac)
	{
		to_exec = ft_strdup(av[i]);
		if (eval_command(&to_exec))
		{
			ft_strdel(&to_exec);
			ft_dprintf(STDERR_FILENO, "%s: env: %s: unknown command.\n",
					g_progname, av[i]);
			return (1);
		}
	}
	ft_construct_tmp_env(av, i);
	if (i == ac)
		ft_print_tables(environ);
	else
		ft_env_exec(to_exec, &(av[i]));
	ft_tabdel(&environ);
	environ = save_env;
	return (0);
}
