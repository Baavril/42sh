/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:12:14 by yberramd          #+#    #+#             */
/*   Updated: 2020/03/08 19:22:09 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

extern struct s_svar	*g_svar;

void			print_double_char(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		ft_putendl(tab[i]);
		i++;
	}
}

static int		count_words(t_tst *tst, int ret)
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

static int		go_to_char(t_tst **tst, char *input)
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

static int		nbr_words(t_tst *tst, char *input)
{
	int	ret;

	ret = 0;
	if ((ret = go_to_char(&tst, input)) != 2)
		return (ret);
	return (count_words(tst, 0));
}

static int		malloc_words(t_tst *tst, int len, int index, char **words)
{
	if (tst->right && tst->c != '\0')
		index = malloc_words(tst->right, len, index, words);
	if (tst->left && tst->c != '\0')
		index = malloc_words(tst->left, len, index, words);
	if (tst->middle && tst->c != '\0')
	{
		len++;
		index = malloc_words(tst->middle, len, index, words);
	}
	if (tst->end == true)
	{
		if (!(words[index] = (char*)malloc(sizeof(char) * (len + 1))))
			return (-1);
		index++;
	}
	return (index);
}

static int		ft_words(t_tst *tst, int len, int index, char **w, char *str)
{
	if (tst->right && tst->c != '\0')
		index = ft_words(tst->right, len, index, w, str);
	if (tst->left && tst->c != '\0')
		index = ft_words(tst->left, len, index, w, str);
	if (tst->middle && tst->c != '\0')
	{
		str[len] = tst->c;
		len++;
		index = ft_words(tst->middle, len, index, w, str);
	}
	if (tst->middle && tst->middle->end == true)
	{
		str[len] = '\0';
		ft_strcat(w[index], str);
		index++;
	}
	return (index);
}

static int		malloc_str(t_tst *tst, int len, int max_len)
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

static int		assign_words(t_tst *tst, char **words, char *input, int len)
{
	int		i;
	char	*str;

	i = 0;
	if (go_to_char(&tst, input) == 0)
		return (-1);
	if ((str = (char*)malloc(sizeof(char)
					* (malloc_str(tst, 0, 0) + ft_strlen(input) + 1))) == NULL)
		return (-1);
	if (malloc_words(tst, ft_strlen(input), 0, words) == -1)
	{
		ft_strdel(&str);
		return (-1);
	}
	while (i < len)
	{
		ft_strcpy(words[i], input);
		i++;
	}
	ft_words(tst, 0, 0, words, str);
	ft_strdel(&str);
	return (1);
}

static char		**ft_binary(t_tst *tst, char *input)
{
	int		len;
	char	**words;

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
	return (words);
}

static int		pos_start(char *input, int start)
{
	if (ft_isspace(input[start]) || input[start] == '|'
			|| input[start] == '&' || input[start] == ';')
		start--;
	if (!ft_isspace(input[start]))
	{
		while (start > 0 && !ft_isspace(input[start])
				&& !(input[start] == '|' || input[start] == '&'
					|| input[start] == ';'))
			start--;
		if (ft_isspace(input[start]) || input[start] == '|'
				|| input[start] == '&' || input[start] == ';')
			start++;
	}
	return (start);
}

int				ft_restart(char *input, int start)
{
	start--;
	while (start >= 0 && !ft_isspace(input[start]) && !(input[start] == '|'
				|| input[start] == '&' || input[start] == ';'))
		start--;
	if (start != -1 && (input[start] == '|'
				|| input[start] == '&' || input[start] == ';'))
		return (1);
	while (start >= 0 && ft_isspace(input[start]))
		start--;
	if (start != -1 && (input[start] == '|'
				|| input[start] == '&' || input[start] == ';'))
		return (1);
	else
		return (0);
}

static char		*ft_assign_words(char *str, int dollar)
{
	int		i;
	int		y;
	char	*tmp;

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

static int		ft_cmp_str(char *str1, char *str2)
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
	int				i;
	int				y;
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

int				ft_auto_completion(t_tst *t, char *input, char ***w, int start)
{
	int		cursor;
	int		ret;
	char	tmp;

	cursor = start;
	start = pos_start(input, start);
	tmp = input[cursor];
	input[cursor] = '\0';
	if (input[start] == '$')
	{
		ret = 1;
		ft_putchar('\n');
		if (input[start + 1] == '{')
			ret = 2;
		if (ft_env_var(&input[start + ret], ret, w) == 0)
		{
			input[cursor] = tmp;
			return (0);
		}
	}
	else if (start == 0 || ft_restart(input, cursor))
	{
		if (((*w) = ft_binary(t, &input[start])) == NULL)
			if (((*w) = ft_path(&input[start])) == NULL)
			{
				input[cursor] = tmp;
				return (0);
			}
	}
	else
	{
		if (((*w) = ft_path(&input[start])) == NULL)
		{
			input[cursor] = tmp;
			return (0);
		}
	}
	if ((*w) && (*w)[0] != NULL && (*w)[1] == NULL)
	{
		input[cursor] = tmp;
		return (2);
	}
	input[cursor] = tmp;
	return (3);
}
