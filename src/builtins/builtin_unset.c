/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2019/12/03 16:21:55 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "libft.h"
#include "builtins.h"
#include "shell_variables.h"

int	unsetvarset(char *argv)
{
	struct s_svar *tmp;
	struct s_svar *relink;

	tmp = g_svar;
	while (g_svar && g_svar->next)
	{
		if (ft_strncmp(g_svar->next->key, argv, ft_strlen(g_svar->next->key) - 1) == 0)
		{
			relink = g_svar->next;
			g_svar->next = g_svar->next->next;
			ft_strdel(&(relink->str));
			ft_strdel(&(relink->key));
			ft_strdel(&(relink->value));
			g_svar = tmp;
			return (0);
			//free(relink);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	if (ft_strncmp(tmp->key, argv, ft_strlen(tmp->key) - 1) == 0)
	{
		g_svar = tmp->next;
		ft_strdel(&(tmp->str));
		ft_strdel(&(tmp->key));
		ft_strdel(&(tmp->value));
		return (0);
	}
	return (1);
}

void	cpytabfrom(char **environ)
{
	int i;
	int len;

	i = 0;
	len = ft_tablen(environ);
	while (environ[i + 1])
	{
		free(environ[i]);
		environ[i] = ft_strdup(environ[i + 1]);
		i++;
	}
	environ[i] = 0;
	free(environ[len - 1]);
}

int	unsetvarenv(char *argv)
{
	int i;
	char *key;
	extern char **environ;

	i = 0;
	while (environ[i])
	{
		key = get_key(environ[i]);
		if (ft_strcmp(key, argv) == 0)
		{
			cpytabfrom(&environ[i]);
			return (0);
		}
		++i;
		ft_strdel(&key);
	}
	return (1);
}

int	cmd_unset(int argc, char **argv)
{
	int i;
	(void)argc;
	extern char **environ;

	i = 1;
	while (argv[i])
	{
		if (unsetvarset(argv[i]) == 0)
			unsetvarenv(argv[i]);
		else
			ft_printf("42sh: unset: `%s' is not a valid identifier\n", argv[i]);
		++i;
	}
	cmd_set(0, NULL);
	while (*environ)
	{
		ft_putendl(*environ);
		environ++;
	}
	return (0);
}
