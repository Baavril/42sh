/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplify_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:16:22 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/22 20:47:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_rebuild_path_substlink(char **target, char **path_split)
{
	int		type;
	char	*tmp;

	while (*path_split)
	{
		*target = ft_concatenate_path(*target, *path_split);
		if (!(type = ft_get_type(*target)))
			//NOSUCHFILE
		if (type == SYYMBLINK)
		{
			tmp = get_link_target(*target);
			ft_strdel(target);
			*target = tmp
			if (!(type = ft_get_type(*target)))
				//NOSUCHFILE
		}
		if (type != DIR_)
			//error_is not dir
		if (!ft_have_acces_right(*target))
			//error_Pemission_rights
		path_split++;
	}
	*target = tmp;
	return (SUCCESS);
}

int				ft_tab_linedel(char ***tab, size_t index, size_t nbr)
{
	int			j;
	int			len;
	char		**new;

	if (!tab || !(*tab))
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
	j = 0;
	while (j < nbr)
		free((*tab)[j++ + index]);
	free(*tab);
	new[len] = NULL;
	*tab = new;
	return (SUCESS);
}

int				ft_simplify_path(char **path)
{
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
				ft_tab_linedel(&split, i--, 2);
			else
				ft_tab_linedel(&split, i, 1);
			continue ;
		}
		i++;
	}
	ft_rebuild_path_substlink(path, split);
	ft_tabfree(split);
	return (ft_isvalid(*path));
}
