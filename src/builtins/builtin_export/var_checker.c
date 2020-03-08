/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vqr_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/08 13:41:16 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell_variables.h"
#include "builtin_export.h"
#include "hash_module.h"
#include "builtins.h"
#include "libft.h"

extern struct s_svar	*g_svar;
extern t_htable			*g_bintable;

static int				testvarlst(char *tmp_n, char *argv, struct s_svar *tmp)
{
	char	*key_name;

	if (!(key_name = get_key(g_svar->str)))
		return (ERROR);
	if (ft_strcmp(key_name, tmp_n) == 0)
	{
		ft_strdel(&(g_svar->str));
		ft_strdel(&(g_svar->value));
		if (!(g_svar->str = ft_strdup(argv)))
			return (ERROR);
		if (!(g_svar->value = ft_strdupfm(argv, '=')))
			return (ERROR);
		ft_strdel(&key_name);
		ft_strdel(&tmp_n);
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

static int				check_if_done(char *str, char **environ)
{
	int	i;
	int	len;

	i = 0;
	len = ft_tablen(environ);
	while (i < len)
	{
		if (ft_strcmp(str, environ[i]) == 0)
			return (ERROR);
		++i;
	}
	return (SUCCESS);
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
			if (check_if_done(g_svar->str, environ) == SUCCESS)
			{
				if (!(keep = realloc_environ(environ, g_svar->str)))
					return (NULL);
			}
			else
				break ;
			g_svar->exp = 1;
			g_svar = tmp;
			return (keep);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	return (environ);
}
