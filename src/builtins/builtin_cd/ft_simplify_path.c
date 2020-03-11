/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplify_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:16:22 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/11 12:26:50 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "builtin_cd.h"
#include "libft.h"

int				g_link_lvl = 0;

static int		ft_check_link(char **to_check, char **target)
{
	char	*tmp;

	tmp = ft_get_link_target(*to_check);
	ft_strdel(to_check);
	if (*tmp == '/')
		*to_check = tmp;
	else
	{
		*to_check = ft_concatenate_path(*target, tmp);
		ft_strdel(&tmp);
	}
	if (++g_link_lvl > LINK_LVL)
		return (EXCEED_LINK_LVL);
	if (ft_gettype(*to_check) == STAT_ERROR)
		return (TARGET_NOT_FOUND);
	return (EXEC_SUCCESS);
}

static int		ft_check_intermediate_target(char **to_check, char **target,
		int opt_p)
{
	int		type;

	if ((type = ft_gettype(*to_check)) == STAT_ERROR)
		return (TARGET_NOT_FOUND);
	if ((type & S_IFMT) == S_IFLNK)
	{
		if ((opt_p))
		{
			if ((type = ft_check_link(to_check, target)) != EXEC_SUCCESS)
				return (type);
			return (ft_simplify_path(to_check, opt_p));
		}
		if ((type = ft_get_targettype(*to_check)) == STAT_ERROR)
			return (TARGET_NOT_FOUND);
	}
	if ((type & S_IFMT) != S_IFDIR)
		return (NOT_DIR);
	if (!ft_get_permission(*to_check))
		return (NO_PERM);
	return (EXEC_SUCCESS);
}

static int		ft_rebuild_path(char **target, char **path_split, int opt_p)
{
	int		type;
	char	*tmp;

	if (!(*path_split))
		*target = ft_strdup("/");
	while (*path_split)
	{
		tmp = ft_concatenate_path(*target, *path_split);
		type = ft_check_intermediate_target(&tmp, target, opt_p);
		ft_strdel(target);
		*target = tmp;
		if (type != EXEC_SUCCESS)
			return (type);
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
	if (len < 0 || index > len
			|| !(new = (char **)ft_memalloc((len + 1) * sizeof(*new))))
		return (ERROR);
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

int				ft_simplify_path(char **path, int opt_p)
{
	int		ret;
	size_t	i;
	char	**split;

	if (!path || !(*path) || !(split = ft_strsplit(*path, "/")))
		return (ERROR);
	ft_strdel(path);
	i = 0;
	while (split[i])
	{
		if (!ft_strcmp(split[i], "."))
			ft_tab_linedel(&split, i, 1);
		else if (!ft_strcmp(split[i], ".."))
		{
			if (i > 0)
				ft_tab_linedel(&split, --i, 2);
			else
				ft_tab_linedel(&split, 0, 1);
		}
		else
			i++;
	}
	ret = ft_rebuild_path(path, split, opt_p);
	ft_tabdel(&split);
	return (ret);
}
