/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaire.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:30:55 by yberramd          #+#    #+#             */
/*   Updated: 2020/03/10 16:38:41 by yberramd         ###   ########.fr       */
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

static void		ft_builtins(char **binaires)
{
	binaires[0] = ft_strdup("echo");
	binaires[1] = ft_strdup("cd");
	binaires[2] = ft_strdup("setenv");
	binaires[3] = ft_strdup("unsetenv");
	binaires[4] = ft_strdup("env");
	binaires[5] = ft_strdup("exit");
}

static int		ft_assign_binary(char **binaires, DIR *dir, int len, int *y)
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

static int		ft_binaires(char **binaires, char **path_dir, int len)
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

	len = ft_nbr_binary(path_dir) + 6;
	if (!(binaires = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	binaires[len] = NULL;
	ft_builtins(binaires);
	if (len > 6)
		ft_binaires(binaires, path_dir, len);
	return (binaires);
}

static t_tst	*first_cpy(char *str, t_tst **tst, int i)
{
	t_tst	*cpy;

	if (!(cpy = (t_tst*)malloc(sizeof(t_tst))))
		return (NULL);
	(*tst) = cpy;
	cpy->left = NULL;
	cpy->right = NULL;
	cpy->middle = NULL;
	cpy->c = str[i];
	cpy->end = false;
	return (cpy);
}

static int		assign_cpy(char *str, t_tst **cpy, int i)
{
	if (!((*cpy)->middle = (t_tst*)malloc(sizeof(t_tst))))
		return (-1);
	(*cpy) = (*cpy)->middle;
	(*cpy)->left = NULL;
	(*cpy)->right = NULL;
	(*cpy)->middle = NULL;
	(*cpy)->c = str[i];
	(*cpy)->end = false;
	return (1);
}

static int		new_word(char *str, t_tst **tst, int i)
{
	t_tst	*cpy;

	if (str[i] != '\0')
	{
		if (!(cpy = first_cpy(str, tst, i)))
			return (-1);
		i++;
	}
	while (str[i] != '\0')
	{
		if (assign_cpy(str, &cpy, i++) == -1)
			return (-1);
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
		if (str[i] == tst->c)
		{
			tst = tst->middle;
			i++;
		}
		if (tst->c != '\0' && str[i] > tst->c && str[i] != '\0')
		{
			if (tst->right != NULL)
				tst = tst->right;
			else
				return (new_word(str, &tst->right, i));
		}
		if (tst->c != '\0' && str[i] < tst->c && str[i] != '\0')
		{
			if (tst->left != NULL)
				tst = tst->left;
			else
				return (new_word(str, &tst->left, i));
		}
	}
	if (tst->c == '\0' && str[i] != '\0')
	{
		tst->c = str[i];
		i++;
	}
	if (str[i] != '\0')
		return (new_word(str, &tst->middle, i));
	if (tst->c != '\0')
		return (last_char(&tst));
	return (1);
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
		path_dir = create_dir(path, 0, 0);
	binaires = create_binary(path_dir);
	if (create_tst(binaires, &tst) == -1)
		del_tst(tst);
	del_double_char(path_dir);
	del_double_char(binaires);
	return (tst);
}
