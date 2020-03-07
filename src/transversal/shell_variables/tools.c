/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/07 16:19:50 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"

struct s_svar	*g_svar;
struct s_pos	*g_pos;

static int		ft_retinstr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] - c == 0)
			return (i);
		i++;
	}
	return (1);
}

char			*ft_strdupfm(char *str, char c)
{
	int		i;
	int		lim;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(str);
	lim = ft_retinstr(str, c) + 1;
	if (len - lim >= 0)
	{
		if (!(ret = (char*)ft_memalloc(sizeof(char) * (len - lim) + 1)))
			return (NULL);
		len = len - lim;
	}
	else
		return (NULL);
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

char			*ft_strdupto(char *str, char c)
{
	int		i;
	int		lim;
	char	*ret;

	i = 0;
	lim = ft_retinstr(str, c) + 1;
	if (!(ret = (char*)malloc(sizeof(char) * (lim + 1))))
		return (NULL);
	while (i < lim)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static int		update_path_vars(char *str)
{
	struct s_svar	*voyager;

	voyager = g_svar;
	while (voyager)
	{
		if (!ft_strncmp(str, voyager->key, ft_strpchr(str, EQUAL) + 1))
		{
			if (ft_strcmp(str, voyager->str))
			{
				ft_strdel(&voyager->value);
				ft_strdel(&voyager->str);
				voyager->value = ft_strdupfm(str, EQUAL);
				voyager->str = ft_strdup(str);
			}
		}
		voyager = voyager->next;
	}
	voyager = g_svar;
	return (0);
}

int				update_intern_vars(void)
{
	int				i;
	int				len;
	extern char		**environ;

	i = 0;
	len = ft_tablen(environ);
	while (i < len)
	{
		if (!ft_strncmp(environ[i], "PWD=", 4)
				|| !ft_strncmp(environ[i], "OLDPWD=", 7))
			update_path_vars(environ[i]);
		++i;
	}
	return (0);
}
