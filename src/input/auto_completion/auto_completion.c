/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:12:14 by yberramd          #+#    #+#             */
/*   Updated: 2019/09/28 20:28:21 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
les taches :
- l'affichage des binaires
- les leaks
- et le path affichage et prise en compte*/

#include "auto_completion.h"
#include <stdio.h>

void	print_double_char(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		ft_putendl(tab[i]);
		i++;
	}
}

static char *ft_dirchr(char *input)
{
	char 	*cur_dir;
	char 	svg;
	char 	*last_bslash;
	int 	i;

	i = 0;
	last_bslash = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '/')
		{
			svg = input[i];
			last_bslash = &input[i];
		}
		i++;
	}
	if (last_bslash != NULL)
	{
		*last_bslash = '\0';
		cur_dir = ft_strdup(input);
		*last_bslash = svg;
	}
	else
		cur_dir = ft_strdup(getenv("PWD"));
	return (cur_dir);
}

static char *ft_last_back_slash(char *input)
{
	int 	i;
	char 	*point;

	i = 0;
	point = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '/')
			point = &input[i + 1];
		i++;
	}
	if (point == NULL)
		point = input;
	return (point);
}

static int	ft_pointchr(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 && !str2)
		return (0);
	while (str1[i] && str2[i] && !ft_isspace(str1[i]))
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] && str2 && !ft_isspace(str1[i]))
		return (0);
	return (1);
}

static char	**ft_path(char *input)// FAIRE ATTENTION AUX FREE
{
	int 			i;
	char			**words;
	struct dirent 	*dirent;
	DIR				*dir;
	char 			*point;

	i = 0;
	dir = NULL;
	if (!(words = (char**)malloc(sizeof(char*) * 64)))//realloc a voir !!!!!!!!!!!!!!!!!
		return (NULL);
	if (input && input[0] == '/')
	{
		printf("PATH\n");
	}
	else if (input)
	{
		point = ft_dirchr(input);
	//	ft_printf("before: point[%s]\n", point);
		if ((dir = opendir(point)) == NULL)
		{
			ft_strdel(&point);
			ft_dprintf(2, "No such file or directory\n");
			return (NULL);
		}
		ft_strdel(&point);
		point = ft_last_back_slash(input);
		//ft_printf("after: point[%s]", point);
		ft_putchar('\n');
		while ((dirent = readdir(dir)) != NULL)//realloc
		{
			if (ft_pointchr(point, dirent->d_name))// add point
			{
				if (*point == '\0' || ft_isspace(*point))
				{
					if (ft_strcmp("..", dirent->d_name) && ft_strcmp(".", dirent->d_name))
					{
						if (dirent->d_type == 4)
						{
							if (!(words[i] = ft_strjoin(dirent->d_name, "/")))
							{
								del_double_char(words);
								return (NULL);
							}
						}
						else
						{
							if (!(words[i] = ft_strdup(dirent->d_name)))
							{
								del_double_char(words);
								return (NULL);
							}
						}
						i++;
					}
				}
				else if (dirent->d_type == 4)
				{
					if (!(words[i] = ft_strjoin(dirent->d_name, "/")))
					{
						del_double_char(words);
						return (NULL);
					}
					i++;
				}
				else
				{
					if (!(words[i] = ft_strdup(dirent->d_name)))
					{
						del_double_char(words);
						return (NULL);
					}
					i++;
				}
			}
		}
	//	printf("--PATH2\n");	
	}
	if (dir)
		closedir(dir);
	words[i] = NULL;
	return (words);
}

static int	count_words(t_tst *tst, int ret)
{
	if (tst->right && tst->c != '\0')
		ret = count_words(tst->right, ret);
	if (tst->left && tst->c != '\0')
		ret = count_words(tst->left, ret);
	if (tst->middle && tst->c != '\0')
		ret = count_words(tst->middle, ret);
	if (tst->end == true)
		ret++;
	return (ret);
}

static int	go_to_char(t_tst **tst, char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0' && (*tst) && (*tst)->c != '\0')
	{
		if ((*tst) && input[i] > (*tst)->c)
			(*tst) = (*tst)->right;
		if ((*tst) && input[i] < (*tst)->c)
			(*tst) = (*tst)->left;
		if ((*tst) && input[i] == (*tst)->c)
		{
			(*tst) = (*tst)->middle;
			i++;
		}
	}
	if (!(*tst) || ((*tst)->c == '\0' && input[i] != '\0'))
		return (0);
	if ((*tst)->c == '\0' && input[i] == '\0')
		return (1);
	return (2);
}

static int	nbr_words(t_tst *tst, char *input)
{
	int	ret;

	ret = 0;
	if ((ret = go_to_char(&tst, input)) != 2)
		return (ret);
	return (count_words(tst, 0));
}

static int	malloc_words(t_tst *tst, int len, int index, char **words)
{
	if (tst->right && tst->c != '\0')
		index = malloc_words(tst->right, len, index, words);
	if (tst->left && tst->c != '\0')
		index = malloc_words(tst->left, len, index, words);
	if (tst->middle && tst->c != '\0')
	{
		len++;
		//printf("%c", tst->c);
		index = malloc_words(tst->middle, len, index, words);
	}
	if (tst->end == true)
	{
		/*printf("\n");
		printf("len_word = [%d]\n", len);
		printf("index_word = [%d]\n", index);
		printf("_____________________________\n");*/
		if (!(words[index] = (char*)malloc(sizeof(char) * (len + 1))))
			return (-1);
		index++;
	}
	return (index);
}

/*static int	ft_words_back(t_tst *tst, int len, int index, char **words)
{
	t_tst *head;

	head = tst;
	while (tst->middle && tst->c != '\0')
	{
		if (tst->end == true)
		{
		}
	}
	return (index);
}*/

/*static int	ft_nbr_words(t_tst *tst)
{
	int	i;

	i = 0;
	return (i);
}*/

static int	ft_words(t_tst *tst, int len, int index, char **words)
{
	if (tst->right && tst->c != '\0')
		index = ft_words(tst->right, len, index, words);
	if (tst->left && tst->c != '\0')
		index = ft_words(tst->left, len, index, words);
	if (tst->middle && tst->c != '\0')
	{
		//printf("len [%d]\n", len);
		//printf("tst-> [%c]\n", tst->c);
		words[index][len] = tst->c;
		len++;
		index = ft_words(tst->middle, len, index, words);
	}
	if (tst->end == true)
	{
		words[index][len] = '\0';
		index++;
	}
	return (index);
}

static int	assign_words(t_tst *tst, char **words, char *input, int len)
{
	int i;

	i = 0;
	if (go_to_char(&tst, input) == 0)
		return (-1);
	//printf("HEAD: [%c]\n", tst->c);
	if (malloc_words(tst, ft_strlen(input), 0, words) == -1)
		return (-1);
	//ASSIG
	while (i < len)
	{
		ft_strcpy(words[i], input);
		i++;
	}
	//printf("HEAD: [%c]\n", tst->c);
	ft_words(tst, ft_strlen(input), 0, words);
	return (1);
}

static char	**ft_binary(t_tst *tst, char *input)
{
	int		len;
	char	**words;

	//printf("\nBINARY\n");
	words = NULL;
	if ((len = nbr_words(tst, input)) == 0)
		return (NULL);
	if (!(words = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	words[len] = NULL;
	if (assign_words(tst, words, input, len) == -1)
	{
		del_double_char(words);
		return (NULL);
	}
	//printf("ft_binary nbr = [%d]\n", len);
	return (words);
}

static int pos_start(char *input, int start)
{
	if (ft_isspace(input[start]))
		start--;
	if (!ft_isspace(input[start]))
	{
		while (start > 0 && !ft_isspace(input[start]))
			start--;
		if (ft_isspace(input[start]))
			start++;
	}
	return (start);
}

int 	ft_auto_completion(t_tst *tst, char *input, char ***words, int start)
{
	start = pos_start(input, start);
	if (((*words) = ft_binary(tst, &input[start])) == NULL)
		if (((*words) = ft_path(&input[start])) == NULL)
			return (0);
	if ((*words) && (*words)[0] != NULL && (*words)[1] == NULL)
		return (2);
	return (3);
}