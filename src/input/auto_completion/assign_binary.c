/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <yberramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:08:45 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/09 20:50:18 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

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

static int		ft_words(t_tst *tst, t_int in, char **w, char *str)
{
	if (tst->right && tst->c != '\0')
		in.index = ft_words(tst->right, in, w, str);
	if (tst->left && tst->c != '\0')
		in.index = ft_words(tst->left, in, w, str);
	if (tst->middle && tst->c != '\0')
	{
		str[in.len++] = tst->c;
		in.index = ft_words(tst->middle, in, w, str);
	}
	if (tst->middle && tst->middle->end == true)
	{
		str[in.len] = '\0';
		ft_strcat(w[in.index++], str);
	}
	return (in.index);
}

int				assign_words(t_tst *tst, char **words, char *input, int len)
{
	int		i;
	char	*str;
	t_int	in;

	i = 0;
	in.index = 0;
	in.len = 0;
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
	ft_words(tst, in, words, str);
	ft_strdel(&str);
	return (1);
}
