/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2020/01/19 13:14:37 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "libft.h"
#include "builtins.h"
#include "shell_variables.h"

extern struct s_svar	*g_svar;

int						unsetvarset(char *argv)
{
	struct s_svar	*tmp;
	struct s_svar	*relink;

	tmp = g_svar;
	while (tmp && tmp->next)
	{
		if (!ft_strncmp(tmp->next->key, argv, ft_strlen(tmp->next->key) - 1))
		{
			relink = tmp->next;
			tmp->next = tmp->next->next;
			ft_strdel(&(relink->str));
			ft_strdel(&(relink->key));
			ft_strdel(&(relink->value));
			return (0);
			//free(relink);
		}
		tmp = tmp->next;
	}
	if (ft_strncmp(g_svar->key, argv, ft_strlen(g_svar->key) - 1) == 0)
	{
		tmp = g_svar;
		g_svar = g_svar->next;
		ft_strdel(&(tmp->str));
		ft_strdel(&(tmp->key));
		ft_strdel(&(tmp->value));
		return (0);
	}
	return (1);
}

void					cpytabfrom(char **environ)
{
	int		i;
	int		len;

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

int						unsetvarenv(char *argv)
{
	int				i;
	char			*key;
	extern char		**environ;

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

int						cmd_unset(int argc, char **argv)
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
