/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:39:26 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/09 23:32:15 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

int	realloc_n;

static char		**ft_realloc(char **words)
{
	char	**tmp;
	int		i;

	i = 0;
	realloc_n *= 2;
	if (!(tmp = (char**)malloc(sizeof(char*) * realloc_n)))
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
	i = 0;
	while (d_name[i] != '\0')
	{
		if (d_name[i] == ' ')
		{
			tmp[y] = '\\';
			y++;
		}
		tmp[y] = d_name[i];
		y++;
		i++;
	}
	if (directory == 4)
	{
		tmp[y] = '/';
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
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

static char		*ft_strdup_bslash(char *input, int length)
{
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!(tmp = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '\\')
			i++;
		tmp[y] = input[i];
		i++;
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}

static char		*ft_dirchr(char *input)
{
	char	*cur_dir;
	char	*last_bslash;
	int		i;
	int		length;

	i = 0;
	length = 0;
	last_bslash = NULL;
	while (input[i] != '\0' && !ft_isspace(input[i]))
	{
		if (input[i] == '/')
			last_bslash = &input[i];
		if (input[i] == '\\')
		{
			i++;
			length--;
		}
		i++;
	}
	if (last_bslash != NULL)
	{
		*last_bslash = '\0';
		if (input[0] == '\0')
			cur_dir = ft_strdup("/");
		else
			cur_dir = ft_strdup_bslash(input, i + length);
		*last_bslash = '/';
	}
	else
		cur_dir = ft_strdup(getenv("PWD"));
	return (cur_dir);
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
	realloc_n = 64;
	if (!(words = (char**)malloc(sizeof(char*) * realloc_n)))
		return (NULL);
	words[0] = NULL;
	if (input)
	{
		point = ft_dirchr(input);
		if ((dir = opendir(point)) == NULL)
		{
			del_double_char(words);
			ft_strdel(&point);
			ft_dprintf(2, "No such file or directory\n");
			return (NULL);
		}
		ft_strdel(&point);
		point = ft_last_back_slash(input);
		ft_putchar('\n');
		while ((dirent = readdir(dir)) != NULL)
		{
			if (ft_pointchr(point, dirent->d_name))
			{
				if (i == realloc_n - 1 && !(words = ft_realloc(words)))
				{
					del_double_char(words);
					return (NULL);
				}
				if (*point == '\0' || ft_isspace(*point))
				{
					if (ft_strcmp("..", dirent->d_name)
							&& ft_strcmp(".", dirent->d_name))
					{
						if (!(words[i] = ft_add_bslash(dirent->d_type,
								dirent->d_name)))
						{
							del_double_char(words);
							return (NULL);
						}
						i++;
					}
				}
				else if (dirent->d_type == 4 || dirent->d_type == 8)
				{
					if (!(words[i] = ft_add_bslash(dirent->d_type,
								dirent->d_name)))
					{
						del_double_char(words);
						return (NULL);
					}
					i++;
				}
			}
			words[i] = NULL;
		}
	}
	if (dir)
		closedir(dir);
	return (words);
}
