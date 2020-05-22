/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:44:56 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/19 14:21:31 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

extern struct s_svar	*g_svar;

int	ft_init_words(int *i, char ***words, char *input)
{
	struct s_svar	*tmp2;

	tmp2 = g_svar;
	while (tmp2)
	{
		if (ft_cmp_str(input, tmp2->key))
			(*i)++;
		tmp2 = tmp2->next;
	}
	if (*i == 0)
	{
		(*words) = NULL;
		return (1);
	}
	if (!((*words) = (char**)malloc(sizeof(char*) * (*i + 1))))
	{
		(*words) = NULL;
		return (0);
	}
	return (2);
}

int	reinitialize_input(char *input, int cursor, char tmp, int ret)
{
	input[cursor] = tmp;
	return (ret);
}

int	init_w_dollar(int start, char *input, char ***w)
{
	int		ret;

	ret = 1;
	ft_putchar('\n');
	if (input[start + 1] == '{')
		ret = 2;
	if (ft_env_var(&input[start + ret], ret, w) == 0)
		return (0);
	return (1);
}
