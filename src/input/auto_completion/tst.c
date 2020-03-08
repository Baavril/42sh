/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaire.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:30:55 by yberramd          #+#    #+#             */
/*   Updated: 2020/03/08 12:13:07 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

void			del_tst(t_tst *tst)
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
}

int				search_tst(t_tst *tst, char *str)
{
	if (tst)
	{
		if ((*str) != '\0')
		{
			if ((*str) == tst->c)
				return (search_tst(tst->middle, (str + 1)));
			if ((*str) > tst->c)
				return (search_tst(tst->right, str));
			if ((*str) < tst->c)
				return (search_tst(tst->left, str));
		}
		if (tst->end == true)
			return (1);
	}
	return (0);
}

static char		**create_dir(char *path_src) // C'est pas un ft_strsplit(path, ":") ca ?
{
	int		i;
	int		len;
	char	*cp;
	char	**dir;
	char	*path;

	i = 0;
	len = 1;
	if (!(path = ft_strdup(path_src)))
		return (NULL);
	while (path[i] != '\0')
	{
		if (path[i] == ':' && path[i + 1] != '\0' && path[i + 1] != ':')
			len++;
		if (path[i] == ':')
			path[i] = '\0';
		i++;
	}
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

static void		ft_builtins(char **binaires)
{
	binaires[0] = ft_strdup("echo");
	binaires[1] = ft_strdup("cd");
	binaires[2] = ft_strdup("alias");
	binaires[3] = ft_strdup("unalias");
	binaires[4] = ft_strdup("hash");
	binaires[5] = ft_strdup("exit");
	binaires[6] = ft_strdup("test");
	binaires[7] = ft_strdup("set");
	binaires[8] = ft_strdup("fc");
	binaires[9] = ft_strdup("fg");
	binaires[10] = ft_strdup("bg");
	binaires[11] = ft_strdup("jobs");
	binaires[12] = ft_strdup("export");
	binaires[13] = ft_strdup("unset");
	binaires[14] = ft_strdup("history");
	binaires[15] = ft_strdup("type");
	binaires[16] = ft_strdup("true");
	binaires[17] = ft_strdup("false");
}

static int		ft_assign_binary(char **binaires, DIR *dir, int len, int y)
{
	struct dirent	*dirent;

	while ((dirent = readdir(dir)))
	{
		if (ft_strcmp(".", dirent->d_name)
				&& ft_strcmp("..", dirent->d_name)
				&& y < len)
		{
			if (!(binaires[y] = ft_strdup(dirent->d_name)))
			{
				del_double_char(binaires);
				return (-1);
			}
			y++;
		}
	}
	return (1);
}

static int		ft_binaires(char **binaires, char **path_dir, int len)
{
	int				i;
	DIR				*dir;

	i = 0;
	while (path_dir[i])
	{
		if ((dir = opendir(path_dir[i])))
			if (ft_assign_binary(binaires, dir, len, BUILTIN_NBR) == -1)
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

static int		ft_nbr_binary(char **path_dir)
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

static char		**create_binary(char **path_dir)
{
	int				len;
	char			**binaires;

	len = ft_nbr_binary(path_dir) + BUILTIN_NBR;
	if (!(binaires = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	binaires[len] = NULL;
	ft_builtins(binaires);
	if (len > BUILTIN_NBR)
		ft_binaires(binaires, path_dir, len);
	return (binaires);
}

static int		new_word(char *str, t_tst **tst, int i)
{
	t_tst	*cpy;

	if (str[i] != '\0')
	{
		if (!(cpy = (t_tst*)malloc(sizeof(t_tst))))
			return (-1);
		(*tst) = cpy;
		cpy->left = NULL;
		cpy->right = NULL;
		cpy->middle = NULL;
		cpy->c = str[i];
		cpy->end = false;
		i++;
	}
	while (str[i] != '\0')
	{
		if (!(cpy->middle = (t_tst*)malloc(sizeof(t_tst))))
			return (-1);
		cpy = cpy->middle;
		cpy->left = NULL;
		cpy->right = NULL;
		cpy->middle = NULL;
		cpy->c = str[i];
		cpy->end = false;
		i++;
	}
	if (i != 0)
	{
		if (!(cpy->middle = (t_tst*)malloc(sizeof(t_tst))))
			return (-1);
		cpy = cpy->middle;
		cpy->c = '\0';
		cpy->end = true;
		cpy->left = NULL;
		cpy->right = NULL;
		cpy->middle = NULL;
	}
	return (1);
}

static int		last_char(t_tst **tst)
{
	t_tst	*cpy;

	cpy = NULL;
	if ((*tst)->middle)
		(*tst)->end = true;
	else
	{
		if (!(cpy = (t_tst*)malloc(sizeof(t_tst))))
			return (-1);
		(*tst)->middle = cpy;
		cpy->c = '\0';
		cpy->end = true;
		cpy->left = NULL;
		cpy->middle = NULL;
		cpy->right = NULL;
	}
	return (1);
}

static int		add_word(char *str, t_tst *tst)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && tst->c != '\0')
	{
		if (str[i] == tst->c && (++i))
			tst = tst->middle;
		else if (str[i] > tst->c)
		{
			if (tst->right == NULL)
				return (new_word(str, &tst->right, i));
			tst = tst->right;
		}
		else if (str[i] < tst->c)
		{
			if (tst->left == NULL)
				return (new_word(str, &tst->left, i));
			tst = tst->left;
		}
	}
	if (tst->c == '\0' && str[i] != '\0')
		tst->c = str[i++];
	if (str[i] != '\0')
		return (new_word(str, &tst->middle, i));
	return ((tst->c != '\0') ? last_char(&tst) : 1);
}

static int		create_tst(char **binaires, t_tst **tst)
{
	int		i;

	i = 0;
	if (binaires && binaires[i] != NULL)
	{
		if (new_word(binaires[i], tst, 0) == -1)
			return (-1);
		i++;
	}
	while (binaires && binaires[i] != NULL)
	{
		if (add_word(binaires[i], *tst) == -1)
			return (-1);
		i++;
	}
	return (1);
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
		path_dir = create_dir(path);
	binaires = create_binary(path_dir);
	if (create_tst(binaires, &tst) == -1)
		del_tst(tst);
	del_double_char(path_dir);
	del_double_char(binaires);
	return (tst);
}
