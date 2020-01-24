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

void	ft_str_swap(char **a, char **b)
{
	char *i;

	i = *a;
	*a = *b;
	*b = i;
}

int		sort_ascii_tab(char **tab)
{
	int i;
	int j;
	int len;

	i = 0;
	j = i + 1;
	len = ft_tablen(tab);
	while (i < (len - 1))
	{
		while (j < len)
		{
			if (ft_strcasecmp(tab[i], tab[j]) < 0)
				ft_str_swap(&tab[i], &tab[j]);
			++j;
		}
		j = i + 1;
		++i;
	}
	return (SUCCESS);
}

char	**ft_globing(char **split, char *token)
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
	int d;

	i = 0;
	j = 0;
	n = 0;
	d = 0;
	tmp = NULL;
	filedata = NULL;
	if (!(dir = (char **)ft_memalloc(sizeof(char *) * 8192)))
		return (NULL);
	while (split[i])
	{
		if (!i)
		{
			if ((dirhandle = opendir(".")))
			{
				j = 0;
				while ((filedata = readdir(dirhandle)))
				{
					if (*(filedata->d_name) != '.')
					{
						dir[j] = ft_strdup(pattern_matching(filedata->d_name, split[i], 3));
						if (!*(dir[j]))
							free(dir[j]);
						else
							++j;
					}
				}
				dir[j] = 0;
				closedir(dirhandle);
			}
			if (!ft_tablen(dir))
				d++;
		}
		else
		{
			j = 0;
			x = 0;
			if (tmp)
				ft_tabdel(&tmp);
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
					closedir(dirhandle);
				}
				dir[x] = 0;
				++j;
			}
			if (!ft_tablen(dir))
				d++;
		}
		++i;
	}
	n = 0;
	if (!d && split[i])
	{
		ptm = (char**)malloc(sizeof(char*) * (ft_tablen(dir) + 1));
		while (dir[n])
		{
			ptm[n] = ft_strdup(dir[n]);
			++n;
		}
		ptm[n] = 0;
		sort_ascii_tab(ptm);
		ft_tabdel(&dir);
		if (tmp)
			ft_tabdel(&tmp);
		return (ptm);
	}
	else
	{
		ptm = (char**)malloc(sizeof(char*) * 2);
		ptm[0] = ft_strdup(token);
		ptm[1] = 0;
	}
	ft_tabdel(&dir);
	if (tmp)
		ft_tabdel(&tmp);
	return (ptm);
}

