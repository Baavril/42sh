/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <yberramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:53:45 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/09 21:21:07 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

static int	ft_assign_binary(char **binaires, DIR *dir, int len, int *y)
{
	struct dirent	*dirent;

	while ((dirent = readdir(dir)))
	{
		if (ft_strcmp(".", dirent->d_name)
				&& ft_strcmp("..", dirent->d_name)
				&& (*y) < len)
		{
			if (!(binaires[(*y)] = ft_strdup(dirent->d_name)))
			{
				del_double_char(binaires);
				return (-1);
			}
			(*y)++;
		}
	}
	return (1);
}

static int	ft_binaires(char **binaires, char **path_dir, int len)
{
	int				i;
	int				y;
	DIR				*dir;

	i = 0;
	y = 6;
	while (path_dir[i])
	{
		if ((dir = opendir(path_dir[i])))
			if (ft_assign_binary(binaires, dir, len, &y) == -1)
			{
				closedir(dir);
				return (-1);
			}
		if (dir)
			closedir(dir);
		i++;
	}
	return (1);
}

static void	ft_builtins(char **binaires)
{
	binaires[0] = ft_strdup("echo");
	binaires[1] = ft_strdup("cd");
	binaires[2] = ft_strdup("setenv");
	binaires[3] = ft_strdup("unsetenv");
	binaires[4] = ft_strdup("env");
	binaires[5] = ft_strdup("exit");
}

static int	ft_nbr_binary(char **path_dir)
{
	int				i;
	int				len;
	DIR				*dir;
	struct dirent	*dirent;

	i = 0;
	len = 0;
	if (path_dir)
		while (path_dir[i])
		{
			if ((dir = opendir(path_dir[i])))
			{
				while (dir && (dirent = readdir(dir)))
				{
					if (ft_strcmp(".", dirent->d_name)
							&& ft_strcmp("..", dirent->d_name))
						len++;
				}
				if (dir)
					closedir(dir);
			}
			i++;
		}
	return (len);
}

char		**create_binary(char **path_dir)
{
	int				len;
	char			**binaires;

	len = ft_nbr_binary(path_dir) + 6;
	if (!(binaires = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	binaires[len] = NULL;
	ft_builtins(binaires);
	if (len > 6)
		ft_binaires(binaires, path_dir, len);
	return (binaires);
}
