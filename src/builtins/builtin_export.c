/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
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
#include "builtins.h"
#include "libft.h"

//char **environ;

void	ft_lstadd_back(t_list **alst, t_list *new_back)
{
	t_list	*voyager;

	if (!alst)
		return ;
	if (!(*alst))
		*alst = new_back;
	else
	{
		voyager = *alst;
		while (voyager->next)
			voyager = voyager->next;
		voyager->next = new_back;
	}
}

void	ft_listadd_back(struct s_svar *new_back)
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

char		*get_key(char *var)
{
	int		i;
	char	*rav;

	i = 0;
	rav = NULL;
	while (var[i] && var[i] != '=')
		i++;
	if (!(rav = ft_strndup(var, i)))
		return (0);
	return (rav);
}

void	ft_prtsrtlst(void)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (g_svar->exp == 1)
			printf("export %s\"%s\"\n", g_svar->key, g_svar->value);
		g_svar = g_svar->next;
	}
	g_svar = tmp;
}

int		checkvarlst(char *argv)
{
	char *key_name;
	char *tmp_name;
	struct s_svar *tmp;

	tmp = g_svar;
	key_name = NULL;
	if (!(tmp_name = get_key(argv)))
		return (0);
	while (g_svar)
	{
		if (!(key_name = get_key(g_svar->str)))
			return (0);
		if (ft_strcmp(key_name, tmp_name) == 0)
		{
			free(g_svar->str);
			free(g_svar->value);
			g_svar->str = ft_strdup(argv);
			g_svar->value = ft_strdupfm(argv, '=');
			free(key_name);
			free(tmp_name);
			g_svar = tmp;
			return (0);
		}
		else
			free(key_name);
		g_svar = g_svar->next;
	}
	free(tmp_name);
	g_svar = tmp;
	return (1);
}

char	**ft_realloc_environ(char **environ, char *str)
{
	int i;
	char **cpy;

	i = 0;
	cpy = ft_tabcpy(environ);
	while (environ[i])
	{
		ft_strdel(&(environ[i]));
		i++;
	}
	free(environ);
	if (!(environ = (char**)malloc(sizeof(char*) * (ft_tablen(cpy) + 2))))
		return (0);
	i = 0;
	while (cpy[i])
	{
		environ[i] = ft_strdup(cpy[i]);
		i++;
	}
	environ[i] = ft_strdup(str);
	environ[++i] = 0;
	return (environ);
}

int		cmd_export(int argc, char **argv)
{
	int i;
	int exp;
	(void)argc;
	extern char **environ;

	i = 0;
	exp = 0;
	if (!(ft_strcmp(argv[i], "export")))
	{
		(argv[i + 1]) ? i++ : ft_prtsrtlst();
		exp = 1;
	}
	/* gerer les options */
	while (argv[i] && ft_strchr(argv[i], '='))
	{
		if (checkvarlst(argv[i]))
		{
			ft_listadd_back(newnodshell(argv[i], exp));
			if (exp == 1)
				environ = ft_realloc_environ(environ, argv[i]);
		}
		i++;
	}
	/* in order to check the environ settings */
	ft_printf("\nInternvars\n");
	cmd_set(0, NULL);
	ft_printf("\nEnviron\n");
	while (*environ)
		ft_putendl(*environ++); 
	return(0);
}
