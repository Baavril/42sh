/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_bslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/07/06 17:35:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"

struct s_quoted		*g_quoted;

static int			ft_delimit_quoted_token(char *str, int *j)
{
	int					lim;
	int					plus;
	struct s_quoted		*q_lst;

	plus = 0;
	if (!(q_lst = (struct s_quoted*)malloc(sizeof(struct s_quoted))))
		return (0);
	q_lst->expand = (str[*j] == '\'');
	q_lst->next = NULL;
	lim = getquotelim(&str[*j]);
	if ((str[*j]) && str[*j] != SQUOTES && str[*j] != DQUOTES
	&& (str[lim + *j]))
		plus = 1;
	if (str[*j] && (str[*j] == DQUOTES || str[*j] == SQUOTES))
	{
		++(*j);
		lim = (lim) ? lim - 1 : 0;
	}
	q_lst->token = dupbtwqlim(&str[*j], lim + plus);
	*j += lim + 1;
	setquotenod(q_lst);
	return (0);
}

static int	token_reconstitutor(char *str, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < k)
	{
		ft_delimit_quoted_token(str, &j);
		++i;
	}
	return (0);
}

char		*token_quotes_generator(char *str)
{
	int		k;

	k = counter_quoted_words(str);
	token_reconstitutor(str, k);
	return (str);
}
