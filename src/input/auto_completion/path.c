/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:39:26 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/23 15:08:40 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"
#include "error.h"

int	g_realloc;

static char		*ft_last_back_slash(char *input)
{
	int		i;
	char	*point;

	i = 0;
	point = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '/')
			point = &input[i + 1];
		i++;
	}
	if (point == NULL)
		point = input;
	return (point);
}

void			ft_assign_tmp(char *d_name, int *i, int *y, char *tmp)
{
	(*i) = 0;
	while (d_name[(*i)] != '\0')
	{
		if (d_name[(*i)] == ' ')
		{
			tmp[(*y)] = '\\';
			(*y)++;
		}
		tmp[(*y)] = d_name[(*i)];
		(*y)++;
		(*i)++;
	}
}

char			**ft_path(char *input)
{
	int				i;
	char			**words;
	struct dirent	*dirent;
	DIR				*dir;
	char			*point;

	i = 0;
	dir = NULL;
	g_realloc = 64;
	if (!(words = (char**)malloc(sizeof(char*) * g_realloc)))
		return (NULL);
	words[0] = NULL;
	if (input)
	{
		if (!(dir = ft_assign_char(input, words)))
			return (NULL);
		point = ft_last_back_slash(input);
		while ((dirent = readdir(dir)) != NULL)
			if (!add_file(dirent, words, &i, point))
				return (NULL);
	}
	if (dir)
		closedir(dir);
	return (words);
}
