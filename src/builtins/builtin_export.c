/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2020/01/19 13:18:48 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

extern struct s_svar	*g_svar;

void					ft_listadd_back(struct s_svar *new_back)
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

char					*get_key(char *var)
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

void					ft_prtsrtlst(void)
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

int						checkvarlst(char *argv)
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

char					**ft_realloc_environ(char **environ, char *str)
{
	int		i;
	char	**cpy;

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

char					**ft_check_ifset(char *to_check, char **environ)
{
	char **keep;
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(to_check, g_svar->str, ft_strlen(to_check)) == 0)
		{
			keep = ft_realloc_environ(environ, g_svar->str);
			g_svar = tmp;
			return (keep);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	return (environ);
}

int						export_opt(char *opt)
{
	if (ft_strcmp(opt, "-p") == 0
	|| ft_strcmp(opt, "--") == 0)
		ft_prtsrtlst();
	else
	{
		ft_printf("42sh: export: %s: invalid option\nexport: usage: export -p\n", opt);
		return (1);
	}
	return (0);
}

int						cmd_export(int argc, char **argv)
{
	int i;
	int flag;
	(void)argc;
	extern char **environ;

	i = 0;
	flag = 0;
	if (ft_strcmp(argv[i], "export") == 0)
	{
		(argv[i + 1]) ? i++ : ft_prtsrtlst();
		flag = 1;
	}
	while (argv[i])
	{
		if (flag == 1 && argv[i][0] == '-' && ft_tablen(argv) == 2)
			return (export_opt(argv[i]));
		if (ft_strchr(argv[i], '='))
		{
			if (checkvarlst(argv[i]))
			{
				ft_listadd_back(newnodshell(argv[i], flag));
				if (flag)
					environ = ft_realloc_environ(environ, argv[i]);
			}
		}
		else
			environ = ft_check_ifset(argv[i], environ);
		++i;
	}
	/* in order to check the environ settings */
	ft_printf("\nInternvars\n");
	cmd_set(1, NULL);
	ft_printf("\nEnviron\n");
	while (*environ)
		ft_putendl(*environ++); 
	return(0);
}
