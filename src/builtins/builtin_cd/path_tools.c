/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:20:22 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/13 16:19:46 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd.h"
#include "libft.h"

char			*ft_concatenate_path(char *src, char *rel_dst)
{
	size_t		src_len;
	size_t		dst_len;
	char		*res_path;

	if (!src && !rel_dst)
		return (NULL);
	if (!rel_dst)
		return (src);
	src_len = ft_strlen(src);
	dst_len = ft_strlen(rel_dst);
	if (!(res_path = ft_memalloc(src_len + dst_len + 2)))
		return (NULL);
	ft_memcpy(res_path, src, src_len);
	res_path[src_len] = '/';
	ft_memcpy(res_path + src_len + 1, rel_dst, dst_len);
	res_path[src_len + dst_len + 1] = '\0';
	return (res_path);
}

static char		*ft_test_cdpaths(char *rel_dst)
{
	size_t	i;
	char	*cdpaths;
	char	**split;

	if (!rel_dst || !(cdpaths = ft_getenv("CD_PATH")))
		return (0);
	i = 0;
	split = ft_strsplit(cdpaths, ":");
	ft_strdel(&cdpaths);
	while (split[i])
	{
		cdpaths = ft_concatenate_path(split[i++], rel_dst);
		if (ft_is_valid_dir(cdpaths))
			break ;
		ft_strdel(&cdpaths);
	}
	ft_tabdel(&split);
	return (cdpaths);
}

int				ft_get_abspath(char **new_pwd)
{
	char	*pwd;
	char	*tmp;

	if (!new_pwd || !(*new_pwd))
		return (ERROR);
	if (**new_pwd != '/')
	{
		pwd = ft_getenv("PWD");
		if ((*new_pwd)[0] == '.'
		&& ((*new_pwd)[1] == '/' 
		|| ((*new_pwd)[1] == '.' && (*new_pwd)[2] == '/')))
			tmp = ft_concatenate_path(pwd, *new_pwd);
		else if (!(tmp = ft_test_cdpaths(*new_pwd)))
			tmp = ft_concatenate_path(pwd, *new_pwd);
		ft_strdel(&pwd);
		ft_strdel(new_pwd);
		*new_pwd = tmp;
	}
	return (EXEC_SUCCESS);
}
