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

#include "auto_completion.h"
#include <stdio.h>

static void	print_double_char(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		ft_putendl(tab[i]);
		i++;
	}
}

static char	**ft_path(t_tst *tst, char *input)
{
	char	**words;

	(void)tst, (void)input;
	words = NULL;
	printf("PATH\n");
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
		printf("%c", tst->c);
		index = malloc_words(tst->middle, len, index, words);
	}
	if (tst->end == true)
	{
		printf("\n");
		printf("len_word = [%d]\n", len);
		printf("index_word = [%d]\n", index);
		printf("_____________________________\n");
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
		printf("len [%d]\n", len);
		printf("tst-> [%c]\n", tst->c);
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
	printf("HEAD: [%c]\n", tst->c);
	if (malloc_words(tst, ft_strlen(input), 0, words) == -1)
		return (-1);
	while (i < len)
	{
		ft_strcpy(words[i], input);
		i++;
	}
	printf("HEAD: [%c]\n", tst->c);
	ft_words(tst, ft_strlen(input), 0, words);
	return (1);
}

static char	**ft_binary(t_tst *tst, char *input)
{
	int		len;
	char	**words;

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
	printf("ft_binary nbr = [%d]\n", len);
	print_double_char(words);
	del_double_char(words);
	return (words);
}

char	**ft_auto_completion(t_tst *tst, char *input)
{
	char	**words;

	if (ft_strchr(input, '/'))
		words = ft_path(tst, input);
	else
		words = ft_binary(tst, input);
	return (words);
}