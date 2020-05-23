/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:30:55 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/23 15:27:52 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void			del_double_char(char **tab2)
{
	int	i;

	i = 0;
	if (tab2)
	{
		while (tab2[i] != NULL)
		{
			ft_strdel(&tab2[i]);
			i++;
		}
		free(tab2);
	}
	tab2 = NULL;
}

int				del_tst(t_tst *tst)
{
	if (tst)
	{
		if (tst->right)
			del_tst(tst->right);
		if (tst->middle)
			del_tst(tst->middle);
		if (tst->left)
			del_tst(tst->left);
		free(tst);
		tst = NULL;
	}
	return (0);
}

static int		nbr_dir(char **p)
{
	int len;
	int	i;

	i = 0;
	len = 1;
	while ((*p)[i] != '\0')
	{
		if ((*p)[i] == ':' && (*p)[i + 1] != '\0' && (*p)[i + 1] != ':')
			len++;
		if ((*p)[i] == ':')
			(*p)[i] = '\0';
		i++;
	}
	return (len);
}

static char		**create_dir(char *path_src, int i, int len)
{
	char	*cp;
	char	**dir;
	char	*path;

	if (!(path = ft_strdup(path_src)))
		return (NULL);
	len = nbr_dir(&path);
	if (!(dir = (char**)malloc(sizeof(char*) * (len + 1))))
	{
		ft_strdel(&path);
		return (NULL);
	}
	dir[len] = NULL;
	cp = path;
	i = 0;
	while (i < len)
	{
		dir[i] = ft_strdup(path);
		while (*path != '\0')
			path++;
		path++;
		i++;
	}
	ft_strdel(&cp);
	return (dir);
}

t_tst			*ft_tst(void)
{
	char	**binaires;
	char	**path_dir;
	char	*path;
	t_tst	*tst;

	tst = NULL;
	path_dir = NULL;
	path = NULL;
	if ((path = getenv("PATH")) != NULL)
		path_dir = create_dir(path, 0, 0);
	binaires = create_binary(path_dir);
	if (create_tst(binaires, &tst) == -1)
		del_tst(tst);
	del_double_char(path_dir);
	del_double_char(binaires);
	return (tst);
}
