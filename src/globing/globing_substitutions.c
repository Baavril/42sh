/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 18:31:11 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "builtin_test.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

char	**ft_globing(char **split)
{
	struct dirent *filedata;
	DIR *dirhandle;
	char **dir;
	char **tmp;
	char **ptm;
	int i;
	int j;
	int x;
	int n;

	i = 0;
	j = 0;
	n = 0;
	filedata = NULL;
	if (!(dir = (char **)malloc(sizeof(char *) * 4096)))
		return (NULL);
	while (split[i])
	{
		if (!i)
		{
			if (!(dirhandle = opendir(".")))
				return (NULL);
			j = 0;
			while ((filedata = readdir(dirhandle)))
			{
				if (*(filedata->d_name) != '.')
				{
					dir[j] = pattern_matching(filedata->d_name, split[i], 3);
					if (!*(dir[j]))
						free(dir[j]);
					else
						++j;
				}
			}
			dir[j] = 0;
		}
		else
		{
			j = 0;
			x = 0;
			tmp = ft_tabcpy(dir);
			while (tmp[j])
			{
				if ((dirhandle = opendir(tmp[j])))
				{
					while ((filedata = readdir(dirhandle)))
					{
						if (*(filedata->d_name) != '.')
						{
							dir[x] = ft_strjoin(ft_strjoin(tmp[j], "/"), pattern_matching(filedata->d_name, split[i], 3));
							if (!(dir[x][ft_strpchr(dir[x], '/') + 1]))
								free(dir[x]);
							else
								++x;
						}
					}
				}
				dir[x] = 0;
				++j;
			}
		}
		++i;
	}
	n = 0;
	ptm = (char**)malloc(sizeof(char*) * (ft_tablen(dir) + 1));
	while (dir[n])
	{
		ptm[n] = ft_strdup(dir[n]);
		++n;
	}
	ptm[n] = 0;
	closedir(dirhandle);
	return (ptm);
}

