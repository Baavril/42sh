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

#include "shell_variables.h"
#include "builtins.h"
#include "builtin_export.h"
#include "libft.h"

extern struct s_svar	*g_svar;

static int				testvarenv(char *tmp_cmp, char *argv)
{
	int			i;
	char		*key_cmp;
	extern char	**environ;

	i = 0;
	key_cmp = NULL;
	while (environ[i])
	{
		if (!(key_cmp = get_key(environ[i])))
			return (ERROR);
		if (ft_strcmp(key_cmp, tmp_cmp) == SUCCESS)
		{
			free(environ[i]);
			if (!(environ[i] = ft_strdup(argv)))
				return (ERROR);
			ft_strdel(&key_cmp);
			ft_strdel(&tmp_cmp);
			return (SUCCESS);
		}
		else
			ft_strdel(&key_cmp);
		++i;
	}
	return (ERROR);
}

static int				checkvarenv(char *argv)
{
	char	*tmp_cmp;

	if (!(tmp_cmp = get_key(argv)))
		return (ERROR);
	if (testvarenv(tmp_cmp, argv) == SUCCESS)
		return (SUCCESS);
	ft_strdel(&tmp_cmp);
	return (ERROR);
}

static int				testvarlst(char *tmp_name, char *argv, struct s_svar *tmp)
{
	char	*key_name;

	if (!(key_name = get_key(g_svar->str)))
		return (ERROR);
	if (ft_strcmp(key_name, tmp_name) == 0)
	{
		ft_strdel(&(g_svar->str));
		ft_strdel(&(g_svar->value));
		if (!(g_svar->str = ft_strdup(argv)))
			return (ERROR);
		if (!(g_svar->value = ft_strdupfm(argv, '=')))
			return (ERROR);
		ft_strdel(&key_name);
		ft_strdel(&tmp_name);
		g_svar = tmp;
		return (SUCCESS);
	}
	else
		ft_strdel(&key_name);
	return (ERROR);
}

int						checkvarlst(char *argv)
{
	char			*tmp_name;
	struct s_svar	*tmp;

	tmp = g_svar;
	if (!(tmp_name = get_key(argv)))
		return (ERROR);
	while (g_svar)
	{
		if (testvarlst(tmp_name, argv, tmp) == SUCCESS)
		{
			checkvarenv(argv);
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	free(tmp_name);
	g_svar = tmp;
	return (ERROR);
}

char					**ft_check_ifset(char *to_check, char **environ)
{
	char			**keep;
	struct s_svar	*tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(to_check, g_svar->str, ft_strlen(to_check)) == 0)
		{
			if (!(keep = realloc_environ(environ, g_svar->str)))
				return (NULL);
			g_svar->exp = 1;
			g_svar = tmp;
			return (keep);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	return (environ);
}