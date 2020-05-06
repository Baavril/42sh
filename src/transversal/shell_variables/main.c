/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2020/03/01 19:00:30 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "libft.h"
#include "prompt.h"
#include "builtins.h"
#include "unistd.h"
#include <sys/types.h>
#include <pwd.h>

extern int		g_ppid;
struct s_svar	*g_svar;
struct s_pos	*g_pos;

void			setenvnod(struct s_svar *new_back)
{
	struct s_svar	*voyager;

	if (!g_svar)
		return ;
	else
	{
		voyager = g_svar;
		while (voyager->next)
			voyager = voyager->next;
		voyager->next = new_back;
	}
}

int				setenvvar(char *key, char *value)
{
	char	*set;

	if (!(set = ft_strjoin(key, value)))
		return (0);
	ft_strdel(&key);
	ft_strdel(&value);
	if (checkvarlst(set))
		setenvnod(newnodshell(set, 0));
	ft_strdel(&set);
	return (0);
}

static void		init_intern_vars(void)
{
	char *tmp;

	tmp = NULL;
	mkprompt(&tmp);
	setenvvar(ft_strdup(PS1), tmp);
	setenvvar(ft_strdup(PS2), ft_strdup(PS2V));
	setenvvar(ft_strdup(PS3), ft_strdup(PS3V));
	setenvvar(ft_strdup(PS4), ft_strdup(PS4V));
	tmp = getcwd(NULL, 0);
	setenvvar(ft_strdup(SH), ft_strdup(tmp));
	ft_strdel(&tmp);
	setenvvar(ft_strdup(PPID), ft_itoa(g_ppid));
	setenvvar(ft_strdup(PID), ft_itoa(getpid()));
	setenvvar(ft_strdup(OPTERR), ft_strdup(OPTERRV));
	setenvvar(ft_strdup(OPTIND), ft_strdup(OPTINDV));
	if (!(tmp = ft_getenv("HOME")))
	{
		tmp = ft_strdup(getpwuid(getuid())->pw_dir);
		setenvvar(ft_strdup(HOME), ft_strdup(tmp));
	}
	setenvvar(ft_strdup(HISTSIZE), ft_strdup(HISTSIZEV));
	setenvvar(ft_strdup(HISTSIZE), ft_strdup(HISTSIZEV));
	setenvvar(ft_strdup(HISTFILE), ft_strjoin(tmp, HISTFILEV));
	ft_strdel(&tmp);
}

int				init_extern_vars(char **env)
{
	int				i;
	int				len;
	struct s_svar	*voyager;

	i = 0;
	len = ft_tablen(env);
	voyager = g_svar;
	while (i < len)
	{
		if (!ft_strncmp(env[i], "PWD=", 4) || !ft_strncmp(env[i], "OLDPWD=", 7)
		|| !ft_strncmp(env[i], "HOME=", 5) || !ft_strncmp(env[i], "LOGNAME=", 8)
		|| !ft_strncmp(env[i], "USER=", 5) || !ft_strncmp(env[i], "TERM=", 5)
		|| !ft_strncmp(env[i], "SHELL=", 6) || !ft_strncmp(env[i], "PATH=", 5)
		|| !ft_strncmp(env[i], "COLORTERM=", 10) || !ft_strncmp(env[i], "_=", 2)
		|| !ft_strncmp(env[i], "USERNAME=", 9)
		|| !ft_strncmp(env[i], "SHLVL=", 6))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		++i;
	}
	g_svar = voyager;
	return (0);
}

int				init_shell_vars(char **env)
{
	g_svar = newnodshell("IFS=_", 0);
	init_extern_vars(env);
	init_intern_vars();
	return (1);
}
