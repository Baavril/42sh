/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2020/03/01 15:37:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "builtins.h"
#include "shell_variables.h"

extern struct s_svar	*g_svar;

static int
	varinlst(struct s_svar *tmp, char *argv, struct s_svar *relink)
{
	while (tmp && tmp->next)
	{
		if (!ft_strncmp(tmp->next->key, argv, ft_strlen(tmp->next->key) - 1))
		{
			relink = tmp->next;
			tmp->next = tmp->next->next;
			ft_strdel(&(relink->str));
			ft_strdel(&(relink->key));
			ft_strdel(&(relink->value));
			free(relink);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (ERROR);
}

static int
	unsetvarset(char *argv)
{
	struct s_svar	*tmp;
	struct s_svar	*relink;

	relink = NULL;
	tmp = g_svar;
	if (ft_isin(EQUAL, argv))
		return (ERROR);
	if (varinlst(tmp, argv, relink) == SUCCESS)
		return (SUCCESS);
	if (ft_strncmp(g_svar->key, argv, ft_strlen(g_svar->key) - 1) == 0)
	{
		tmp = g_svar;
		g_svar = g_svar->next;
		ft_strdel(&(tmp->str));
		ft_strdel(&(tmp->key));
		ft_strdel(&(tmp->value));
		return (SUCCESS);
	}
	return (ERROR);
}

static int
	cpytabfrom(char **environ)
{
	int		i;
	int		len;

	i = 0;
	len = ft_tablen(environ);
	while (environ[i + 1])
	{
		free(environ[i]);
		if (!(environ[i] = ft_strdup(environ[i + 1])))
			return (ERROR);
		++i;
	}
	free(environ[len - 1]);
	environ[i] = 0;
	return (SUCCESS);
}

static int
	unsetvarenv(char *argv)
{
	int				i;
	char			*key;
	extern char		**environ;

	i = 0;
	while (environ[i])
	{
		key = get_key(environ[i]);
		if (!(ft_strcmp(key, argv)))
		{
			if (cpytabfrom(&environ[i]) == SUCCESS)
			{
				ft_strdel(&key);
				return (SUCCESS);
			}
		}
		++i;
		ft_strdel(&key);
	}
	return (ERROR);
}

int
	cmd_unset(int argc, char **argv)
{
	int			i;
	int			ret;
	extern char	**environ;

	i = 1;
	ret = 0;
	(void)argc;
	while (argv[i])
	{
		if (unsetvarset(argv[i]) == SUCCESS)
			unsetvarenv(argv[i]);
		else if (unsetvarenv(argv[i]) == ERROR)
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: unset: `%s' is not a valid identifier.\n", argv[i]);
			ret++;
		}
		++i;
	}
	return ((ret) ? ERROR : SUCCESS);
}
