/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2019/12/03 16:21:55 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "libft.h"
#include "prompt.h"

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

struct s_svar	*newnodshell(char *env, int exp)
{
	struct s_svar *svar_lst;

	svar_lst = NULL;
	if (*env)
	{
		if (!(svar_lst = (struct s_svar*)malloc(sizeof(struct s_svar))))
			return (NULL);
		svar_lst->str = ft_strdup(env);
		svar_lst->key = ft_strdupto(env, '=');
		svar_lst->value = ft_strdupfm(env, '=');
		svar_lst->exp = exp;
		svar_lst->next = NULL;
	}
	return (svar_lst);
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

static void		init_intern_vars()
{
	char *tmp;

	tmp = NULL;
	g_svar = newnodshell("IFS='_'", 0);
	mkprompt(&tmp);
	setenvvar(ft_strdup(PS1), tmp);
	setenvvar(ft_strdup(PS2), ft_strdup(PS2V));
	setenvvar(ft_strdup(PS3), ft_strdup(PS3V));
	setenvvar(ft_strdup(PS4), ft_strdup(PS4V));
	tmp = getcwd(NULL, 0);
	setenvvar(ft_strdup(SH), ft_strdup(tmp));
	ft_strdel(&tmp);
	setenvvar(ft_strdup(PPID), ft_itoa(getppid()));
	setenvvar(ft_strdup(OPTERR), ft_strdup(OPTERRV));
	setenvvar(ft_strdup(OPTIND), ft_strdup(OPTINDV));
	setenvvar(ft_strdup(HISTSIZE), ft_strdup(HISTSIZEV));
	tmp = ft_getenv("HOME");
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
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "HOME=", 5))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "LOGNAME=", 8))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "USER=", 5))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "USERNAME=", 9))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "TERM=", 5))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "SHELL=", 6))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "PATH=", 5))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "COLORTERM=", 10))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			setenvnod(newnodshell(env[i], 1));
			g_svar = g_svar->next;
		}
		else if (!ft_strncmp(env[i], "_=", 2))
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
	init_intern_vars();
	init_extern_vars(env);
	return (1);
}
