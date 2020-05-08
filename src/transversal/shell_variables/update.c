/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/07 16:19:31 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"
#include "prompt.h"

struct s_svar	*g_svar;

char			*ret_prompt_value(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!(ret = (char*)ft_memalloc(sizeof(char)
	* (ft_strplen(str) + 1))))
		return (0);
	while (str[i])
	{
		if (str[i] == '\033')
		{
			while (str[i] != 'm')
				++i;
			++i;
		}
		if (ft_isprint(str[i]))
			ret[j++] = str[i];
		++i;
		if (str[i] == ' ')
			break ;
	}
	return (ret);
}

char			*get_prompt_value(void)
{
	struct s_svar	*voyager;

	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PS1)))
			return (ret_prompt_value(voyager->value));
		voyager = voyager->next;
	}
	return (NULL);
}

int				set_new_prompt_var(char *new)
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

int				update_prompt_var(void)
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
