/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <yberramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:45:35 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/09 20:51:01 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

int			go_to_char(t_tst **tst, char *input)
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

static int	nbr_words(t_tst *tst, char *input)
{
	int	ret;

	ret = 0;
	if ((ret = go_to_char(&tst, input)) != 2)
		return (ret);
	return (count_words(tst, 0));
}

char		**ft_binary(t_tst *tst, char *input)
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
