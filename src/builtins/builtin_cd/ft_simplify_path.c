/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplify_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:16:22 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/23 18:26:02 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "builtin_cd.h"
#include "libft.h"

static int		ft_rebuild_path_substlink(char **target, char **path_split)
{
	int		type;
	char	*tmp;

	while (*path_split)
	{
//		ft_dprintf(2, "PATH_BUILDING:  in: %s    %s\n", *target, *path_split);
		tmp = ft_concatenate_path(*target, *path_split);
		ft_strdel(target);
		*target = tmp;
//		ft_dprintf(2, "PATH_BUILDING: out: %s\n", *target);
		if ((type = ft_gettype(*target)) == STAT_ERROR)
		{
			//NOSUCHFILE OR DIR
			return (TARGET_NOT_FOUND);
		}
		if ((type & S_IFLNK))
		{
//			ft_dprintf(2, "PATH_BUILDING: link-found\n");
			tmp = ft_get_link_target(*target);
			ft_strdel(target);
			*target = tmp;
			if (!(type = ft_gettype(*target)))
			{
				//NOSUCHFILE OR DIR
				return (TARGET_NOT_FOUND);
			}
		}
		if (!(type & S_IFDIR))
		{
			//%s: cd: %s: Not a directory. g_progname, av[g_optind]
			return (NOT_DIR);
		}
		if (!ft_get_permission(*target))
		{
			//%s: cd: %s: Pemission denied.", g_progname, av[g_optind]
			return (NO_PERM);
		}
		path_split++;
	}
	return (EXEC_SUCCESS);
}

int				ft_tab_linedel(char ***tab, int index, int nbr)
{
	int			j;
	int			len;
	char		**new;

	if (!tab || !(*tab) || index < 0 || nbr <= 0)
		return (ERROR);
	j = -1;
	len = ft_tablen(*tab) - nbr;
	if (len < 0 || index > len)
		return (ERROR);
	new = (char **)ft_memalloc((len + 1) * sizeof(*new)); //ft_memcheck;
	while (++j < index)
		new[j] = (*tab)[j];
	while (j < len)
	{
		new[j] = (*tab)[j + nbr];
		j++;
	}
	j = -1;
	while (++j < nbr)
		free((*tab)[j + index]);
	free(*tab);
	new[len] = NULL;
	*tab = new;
	return (EXEC_SUCCESS);
}

int				ft_simplify_path(char **path)
{
	int ret;
	size_t	i;
	char	**split;

	if (!path || !(*path) || !(split = ft_strsplit(*path, "/")))
		return (ERROR);
	ft_strdel(path);
	i = 0;
	while (split[i])
	{
		if (!ft_strcmp(split[i], "."))
		{
			ft_tab_linedel(&split, i, 1);
			continue ;
		}
		if (!ft_strcmp(split[i], ".."))
		{
			if (i > 0)
				ft_tab_linedel(&split, --i, 2);
			else
				ft_tab_linedel(&split, 0, 1);
			continue ;
		}
		i++;
	}
	ret = ft_rebuild_path_substlink(path, split);
//	ft_dprintf(2, "PATH_BUILDING: final simple: %s\n", *path);
	ft_tabdel(&split);
	return (ret);
}
