/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaire.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:30:55 by yberramd          #+#    #+#             */
/*   Updated: 2019/09/19 18:32:47 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "auto_completion.h"

/*JUSTE UN TEST POUR L'AUTO_COMPLETION*/
void		del_double_char(char **tab2)
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

void		del_tst(t_tst *tst)
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

int		search_tst(t_tst *tst, char *str)
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

/*static void	print_double_char(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		ft_putendl(tab[i]);
		i++;
	}
}*/

static char	**create_dir(char *path_src)/*a modifier*/
{
	int		i;
	int		len;
	char	 *cp;
	char 	**dir;
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
	binaires[2] = ft_strdup("setenv");
	binaires[3] = ft_strdup("unsetenv");
	binaires[4] = ft_strdup("env");
	binaires[5] = ft_strdup("exit");
}

static int		ft_binaires(char **binaires, char **path_dir, int len)
{
	int	i;
	int	y;
	DIR		*dir;
	struct dirent	*dirent;

	i = 0;
	y = 6;
	while (path_dir[i])
	{
		if ((dir = opendir(path_dir[i])))
		{
			while ((dirent = readdir(dir)))
			{
				if (ft_strcmp(".", dirent->d_name) && ft_strcmp("..", dirent->d_name)
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
			closedir(dir);
		}
		i++;
	}
	return (1);
}

static int		ft_nbr_binary(char **path_dir)
{
	int		i;
	int		len;
	DIR		*dir;
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
					if (ft_strcmp(".", dirent->d_name) && ft_strcmp("..", dirent->d_name))
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

static	int	new_word(char *str, t_tst **tst, int i)/*a coriger jeu de pointeur*/
{
	t_tst	*cpy;

	if (str[i] != '\0')
	{
		if (!(cpy = (t_tst*)malloc(sizeof(t_tst))))//ajout de la fonction DEL !!!
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
		if (!(cpy->middle = (t_tst*)malloc(sizeof(t_tst))))//ajout de la fonction DEL !!!
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
		if (!(cpy->middle = (t_tst*)malloc(sizeof(t_tst))))//ajout de la fonction DEL !!!
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

static	int	last_char(t_tst **tst)/*a coriger jeu de pointeur*/
{
	if ((*tst)->middle)
		(*tst)->end = true;
	else
	{
		if (!((*tst)->middle = (t_tst*)malloc(sizeof(t_tst))))//ajout de la fonction DEL !!!
			return (-1);
		(*tst) = (*tst)->middle;
		(*tst)->c = '\0';
		(*tst)->end = true;
		(*tst)->left = NULL;
		(*tst)->middle = NULL;
		(*tst)->right = NULL;
	}
	return (1);
}

static	int	add_word(char *str, t_tst *tst)/*a coriger jeu de pointeur*/
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
	return (last_char(&tst));
}

static	int		create_tst(char **binaires, t_tst **tst)
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

t_tst	*ft_tst()
{
	char	**binaires;
	char	**path_dir;
	char	*path;
	t_tst	*tst;

	tst = NULL;
	path_dir = NULL;
	path = NULL;
	if	((path = getenv("PATH")) != NULL)
		path_dir = create_dir(path);// dir peut etre = a NULL
	binaires = create_binary(path_dir);
	if (create_tst(binaires, &tst) == -1)
		del_tst(tst);
	del_double_char(path_dir);
	del_double_char(binaires);
	return (tst);
}
