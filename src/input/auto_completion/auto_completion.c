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

extern struct s_svar	*g_svar;

int realloc_n;

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
	while (input[i] != '\0' && !ft_isspace(input[i]))
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
		if (input[0] == '\0')
			cur_dir = ft_strdup("/");
		else
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

static char 	**ft_realloc(char **words)
{
	char 	**tmp;
	int 	i;

	i = 0;
	realloc_n *= 2;
	if (!(tmp = (char**)malloc(sizeof(char*) * realloc_n)))
		return (NULL);
	while (words[i] != NULL)
	{
		tmp[i] = words[i];
		i++;
	}
	tmp[i] = NULL;
	free(words);
	words = tmp;
	return (words);
}

static char		**ft_path(char *input)// FAIRE ATTENTION AUX FREE
{
	int 			i;
	char			**words;
	struct dirent 	*dirent;
	DIR				*dir;
	char 			*point;

	i = 0;
	dir = NULL;
	realloc_n = 64;
	if (!(words = (char**)malloc(sizeof(char*) * realloc_n)))
		return (NULL);
	if (input)
	{
		point = ft_dirchr(input);
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
				if (i == realloc_n - 1 && !(words = ft_realloc(words)))
				{
					del_double_char(words);
					return (NULL);
				}
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
				else if (dirent->d_type == 8)
				{
					if (!(words[i] = ft_strdup(dirent->d_name)))
					{
						del_double_char(words);
						return (NULL);
					}
					i++;
				}
			}
			words[i] = NULL;
		}
	//	printf("--PATH2\n");	
	}
	if (dir)
		closedir(dir);
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

// A VOIR PB LSM LSMP....

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

static int	ft_words(t_tst *tst, int len, int index, char **words, char *str)
{
	if (tst->right && tst->c != '\0')
		index = ft_words(tst->right, len, index, words, str);
	if (tst->left && tst->c != '\0')
		index = ft_words(tst->left, len, index, words, str);
	if (tst->middle && tst->c != '\0')
	{
		//printf("len [%d]\n", len);
		//printf("tst-> [%c]\n", tst->c);
		str[len] = tst->c;
		len++;
		index = ft_words(tst->middle, len, index, words, str);
	}
	if (tst->middle && tst->middle->end == true)
	{
		str[len] = '\0';
		ft_strcat(words[index], str);
		index++;
	}
	return (index);
}

static int 	malloc_str(t_tst *tst, int len, int max_len)
{
	if (tst->right && tst->c != '\0')
		max_len = malloc_str(tst->right, len, max_len);
	if (tst->left && tst->c != '\0')
		max_len = malloc_str(tst->left, len, max_len);
	if (tst->middle && tst->c != '\0')
	{
		len++;
		max_len = malloc_str(tst->middle, len, max_len);
	}
	if (tst->end == true)
	{
		if (len > max_len)
			max_len = len;
	}
	return (max_len);
}

static int	assign_words(t_tst *tst, char **words, char *input, int len)
{
	int 	i;
	char 	*str;

	i = 0;
	if (go_to_char(&tst, input) == 0)
		return (-1);
	if ((str = (char*)malloc(sizeof(char) * (malloc_str(tst, 0, 0) + ft_strlen(input) + 1))) == NULL)
		return (-1);
	if (malloc_words(tst, ft_strlen(input), 0, words) == -1)
	{
		ft_strdel(&str);
		return (-1);
	}
	//ASSIG
	while (i < len)
	{
		ft_strcpy(words[i], input);
		i++;
	}
	//printf("HEAD: [%c]\n", tst->c);
	ft_words(tst, 0, 0, words, str);
	ft_strdel(&str);
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
	ft_putchar('\n');
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
	if (ft_isspace(input[start]) || input[start] == '|' || input[start] == '&' || input[start] == ';')
		start--;
	if (!ft_isspace(input[start]))
	{
		while (start > 0 && !ft_isspace(input[start]) && !(input[start] == '|' || input[start] == '&' || input[start] == ';'))
			start--;
		if (ft_isspace(input[start]) || input[start] == '|' || input[start] == '&' || input[start] == ';')
			start++;
	}
	return (start);
}

int 	ft_restart(char *input, int start)
{
	start--;
	while (start >= 0 && !ft_isspace(input[start]) && !(input[start] == '|' || input[start] == '&' || input[start] == ';'))
		start--;
	if (start != -1 && (input[start] == '|' || input[start] == '&' || input[start] == ';'))
		return (1);
	while (start >= 0 && ft_isspace(input[start]))
		start--;
	if (start != -1 && (input[start] == '|' || input[start] == '&' || input[start] == ';'))
		return (1);
	else
		return (0);
}

static char 	*ft_assign_words(char *str, int dollar)
{
	int 	i;
	int 	y;
	char 	*tmp;

	i = 0;
	y = 0;
	if (dollar == 1)
	{
		if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
			return (NULL);
		tmp[y] = '$';
		y++;
		while (str[i + 1] != '\0')
		{
			tmp[y] = str[i];
			i++;
			y++;
		}
	}
	else
	{
		if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(str) + 3))))
			return (NULL);
		tmp[0] = '$';
		tmp[1] = '{';
		y += 2;
		while (str[i + 1] != '\0')
		{
			tmp[y] = str[i];
			i++;
			y++;
		}
		tmp[y] = '}';
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}

static int	ft_cmp_str(char *str1, char *str2)
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

static int		ft_env_var(char *input, int dollar, char ***words)
{
	int 			i;
	int 			y;
	struct s_svar	*tmp;
	struct s_svar	*tmp2;

	i = 0;
	y = 0;
	tmp = g_svar;
	tmp2 = g_svar;
	while (tmp2)
	{
		if (ft_cmp_str(input, tmp2->key))
			i++;
		tmp2 = tmp2->next;
	}
	if (i == 0)
	{
		(*words) = NULL;
		return (1);
	}
	if (!((*words) = (char**)malloc(sizeof(char*) * (i + 1))))
	{
		(*words) = NULL;
		return (0);
	}
	while (tmp)
	{
		if (ft_cmp_str(input, tmp->key))
		{
			if (!((*words)[y] = ft_assign_words(tmp->key, dollar)))
			{
				(*words) = NULL;
				del_double_char((*words));
				return (0);
			}
			y++;
			(*words)[y] = NULL;
		}
		tmp = tmp->next;
	}
	return (1);
}

int 	ft_auto_completion(t_tst *tst, char *input, char ***words, int start)
{
	int 	cursor;
	int 	ret;
	char 	tmp;

	cursor = start;
	start = pos_start(input, start);
	tmp = input[cursor];
	input[cursor] = '\0';
	/*c'est la structure externe g_svar qui t'interesse -> dedans tu trouveras char *str qui contient 
	"key=value" ainsi que char *key qui contient "key=" ou "key" je sais plus et char *var qui contient "var"
	Sinon, j'ai ecrit deux fonctions getshvar et setshvar dans mon module de maths si tu veux : dans expansion/maths_expansion/shvar_tools.c
	*/
	if (input[start] == '$')
	{
		ret = 1;
		ft_putchar('\n');
		if (input[start + 1] == '{')// a voir
			ret = 2;
		if (ft_env_var(&input[start + ret], ret, words) == 0)
		{
			input[cursor] = tmp;
			return (0);
		}
	}
	else if (start == 0 || ft_restart(input, cursor))
	{
		if (((*words) = ft_binary(tst, &input[start])) == NULL)
			if (((*words) = ft_path(&input[start])) == NULL)
			{
				input[cursor] = tmp;
				return (0);
			}
	}
	else
	{
		if (((*words) = ft_path(&input[start])) == NULL)
		{
			input[cursor] = tmp;
			return (0);
		}
	}
	if ((*words) && (*words)[0] != NULL && (*words)[1] == NULL)
	{
		input[cursor] = tmp;
		return (2);
	}
	input[cursor] = tmp;
	return (3);
}
