/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 14:52:43 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/23 15:07:43 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"
#include "error.h"

extern int	g_realloc;

static char		**ft_realloc(char **words)
{
	char	**tmp;
	int		i;

	i = 0;
	g_realloc *= 2;
	if (!(tmp = (char**)malloc(sizeof(char*) * g_realloc)))
		return (NULL);
	while (words[i] != NULL)
	{
		tmp[i] = words[i];
		i++;
	}
	tmp[i] = NULL;
	free(words);
	words = tmp;
	return (words);
}

static int		ft_pointchr(char *str1, char *str2)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (!str1 && !str2)
		return (0);
	while (str1[y] && str2[i] && !ft_isspace(str1[y]))
	{
		if (str1[y] == '\\')
			y++;
		if (str1[y] != str2[i] && str1[y] != '\0')
			return (0);
		if (str1[y] != '\0')
		{
			i++;
			y++;
		}
	}
	if (str1[y] && str2 && !ft_isspace(str1[y]))
		return (0);
	return (1);
}

static char		*ft_add_bslash(int directory, char *d_name)
{
	int		i;
	int		y;
	int		space;
	char	*tmp;

	i = 0;
	y = 0;
	space = 0;
	while (d_name[i] != '\0')
	{
		if (d_name[i] == ' ')
			space++;
		i++;
	}
	if (directory == 4)
		space++;
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(d_name) + space + 1))))
		return (NULL);
	ft_assign_tmp(d_name, &i, &y, tmp);
	if (directory == 4)
		tmp[y++] = '/';
	tmp[y] = '\0';
	return (tmp);
}

static int		ft_assign_words(struct dirent *dirent, char **words, int *i,
									int flag)
{
	if (flag == 1)
	{
		if (ft_strcmp("..", dirent->d_name) && ft_strcmp(".", dirent->d_name))
		{
			if (!(words[(*i)] = ft_add_bslash(dirent->d_type, dirent->d_name)))
			{
				del_double_char(words);
				return (0);
			}
			(*i)++;
		}
	}
	else
	{
		if (!(words[(*i)] = ft_add_bslash(dirent->d_type, dirent->d_name)))
		{
			del_double_char(words);
			return (0);
		}
		(*i)++;
	}
	return (1);
}

int				add_file(struct dirent *dirent, char **words, int *i,
								char *point)
{
	if (ft_pointchr(point, dirent->d_name))
	{
		if ((*i) == g_realloc - 1 && !(words = ft_realloc(words)))
		{
			del_double_char(words);
			return (0);
		}
		if (*point == '\0' || ft_isspace(*point))
		{
			if (!ft_assign_words(dirent, words, i, 1))
				return (0);
		}
		else if (dirent->d_type == 4 || dirent->d_type == 8)
			if (!ft_assign_words(dirent, words, i, 2))
				return (0);
	}
	words[(*i)] = NULL;
	return (1);
}
