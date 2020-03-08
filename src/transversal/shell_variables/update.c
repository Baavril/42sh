/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2020/03/08 11:09:18 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"
#include "prompt.h"

struct s_svar		*g_svar;

int					update_intern_vars(void)
{
	int				i;
	int				len;
	extern char		**environ;
	struct s_svar	*voyager;

	i = 0;
	voyager = g_svar;
	len = ft_tablen(environ);
	while (i < len)
	{
		if (!ft_strncmp(environ[i], "PWD=", 4))
		{
			while (voyager)
			{
				if (!ft_strncmp(environ[i], voyager->key, 4))
				{
					if (ft_strcmp(environ[i], voyager->str))
					{
						ft_strdel(&voyager->value);
						ft_strdel(&voyager->str);
						voyager->value = ft_strdupfm(environ[i], '=');
						voyager->str = ft_strdup(environ[i]);
					}
				}
				voyager = voyager->next;
			}
			voyager = g_svar;
		}
		else if (!ft_strncmp(environ[i], "OLDPWD=", 7))
		{
			while (voyager)
			{
				if (!ft_strncmp(environ[i], voyager->key, 4))
				{
					if (ft_strcmp(environ[i], voyager->str))
					{
						ft_strdel(&voyager->value);
						ft_strdel(&voyager->str);
						voyager->value = ft_strdupfm(environ[i], '=');
						voyager->str = ft_strdup(environ[i]);
					}
				}
				voyager = voyager->next;
			}
			voyager = g_svar;
		}
		++i;
	}
	return (0);
}

static char			*cpy_prompt(struct s_svar *voyager)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!(ret = ft_strnew(ft_strplen(voyager->value))))
		return (NULL);
	while (voyager->value[i])
	{
		if (voyager->value[i] == '\033')
		{
			while (voyager->value[i] != 'm')
				++i;
			++i;
		}
		if (ft_isprint(voyager->value[i]))
			ret[j++] = voyager->value[i];
		if (voyager->value[++i] == ' ')
			break ;
	}
	return (ret);
}

char				*get_prompt_value(void)
{
	char			*ret;
	struct s_svar	*voyager;

	ret = NULL;
	voyager = g_svar;
	while ((voyager) && (ft_strcmp(voyager->key, PS1)))
		voyager = voyager->next;
	if ((voyager))
		ret = cpy_prompt(voyager);
	return (ret);
}

int					set_new_prompt_var(char *new)
{
	struct s_svar	*voyager;

	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PS1)))
		{
			ft_strdel(&voyager->value);
			voyager->value = ft_strdup(new);
			return (0);
		}
		voyager = voyager->next;
	}
	return (0);
}

int					update_prompt_var(void)
{
	int				i;
	char			*tmp1;
	char			*tmp2;
	extern char		**environ;

	i = 0;
	if (!(tmp2 = get_prompt_value()))
		return (0);
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "PWD=", 4)
				|| !ft_strncmp(environ[i], "OLDPWD=", 7))
			if (!(ft_strcmp(tmp2, &environ[i][ft_strpchr(environ[i], '=')
							+ 1])))
			{
				mkprompt(&tmp1);
				set_new_prompt_var(tmp1);
				ft_strdel(&tmp1);
				ft_strdel(&tmp2);
				return (0);
			}
		++i;
	}
	ft_strdel(&tmp2);
	return (0);
}
