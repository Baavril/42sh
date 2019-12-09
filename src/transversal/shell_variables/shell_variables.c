/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
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

struct s_svar *g_svar;

void	listadd_back(struct s_svar *new_back)
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

int	ft_retinstr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] - c == 0)
			return (i);
		i++;
	}
	return (1);
}

char	*ft_strdupfm(char *str, char c)
{
	int i;
	int	lim;
	int	len;
	char *ret;

	i = 0;
	len = ft_strlen(str);
	lim = ft_retinstr(str, c) + 1;
	if (len - lim)
	{
		if (!(ret = (char*)malloc(sizeof(char) * (len - lim) + 1)))
			return (NULL);
		len = len - lim;
	}
	else if (!(len - lim))
	{
		if (!(ret = (char*)malloc(sizeof(char) * (lim - len) + 1)))
			return (NULL);
		len = lim - len;
	}
	while (len)
	{
		ret[i] = str[lim];
		len--;
		i++;
		lim++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strdupto(char *str, char c)
{
	int	i;
	int	lim;
	char *ret;

	i = 0;
	lim = ft_retinstr(str, c) + 1;
	if (!(ret = (char*)malloc(sizeof(char) * lim + 1)))
		return (NULL);
	while (i < lim)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	tablen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		++i;
	return (i);
}

struct s_svar	*newnodshell(char *env, int exp)
{
	struct s_svar *svar_lst;

	if (*env)
	{
		if (!(svar_lst = (struct s_svar*)malloc(sizeof(struct s_svar))))
			return (NULL);
		svar_lst->str = ft_strdup(env);
		svar_lst->key = ft_strdupto(env, '=');
		svar_lst->value = ft_strdupfm(env, '=');
		svar_lst->exp = exp;
	}
	svar_lst->next = NULL;
	return (svar_lst);
}

void	setenvvar(char *key, char *value)
{
	char	*set;

	set = ft_strjoin(key, value);
	listadd_back(newnodshell(set, 0));
	ft_strdel(&set);
}

void init_intvars()
{
	setenvvar(PS1, PS1V);
	setenvvar(PS2, PS2V);
	setenvvar(PS3, PS3V);
	setenvvar(PS4, PS4V);
	setenvvar(HISTSIZE, HISTSIZEV);
}

int	init_shellvars(char **env)
{
	int i;
	int len;
	struct s_svar *voyager;

	i = 1;
	if (!(g_svar = malloc(sizeof(*g_svar) * (tablen(env) + 1))))
			return (0);
	len = tablen(env);
	g_svar = newnodshell(env[0], 1);
	voyager = g_svar;
	while (i < len)
	{
		listadd_back(newnodshell(env[i++], 1));
		g_svar = g_svar->next;
	}
	init_intvars();
	g_svar = voyager;
	return (1);
}
