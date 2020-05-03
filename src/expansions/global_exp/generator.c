/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_bslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/15 16:39:30 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"

struct s_quoted	*g_quoted;

static int	token_starter(char *str, int *j, int *i)
{
	struct s_quoted	*q_lst;

	q_lst = NULL;
	if (!(q_lst = (struct s_quoted*)malloc(sizeof(struct s_quoted))))
		return (0);
	q_lst->expand = 0;
	q_lst->token = dupbtwq(&str[*j]);
	while (str[*j] && (str[*j] != DQUOTES && str[*j] != SQUOTES))
		++(*j);
	++(*i);
	q_lst->next = NULL;
	g_quoted = q_lst;
	return (0);
}

static int	token_concatenator(char *str, int *j, int *i, int lim)
{
	struct s_quoted	*q_lst;

	q_lst = NULL;
	if (!(q_lst = (struct s_quoted*)malloc(sizeof(struct s_quoted))))
		return (0);
	lim = getquotelim(&str[*j]);
	q_lst->expand = isexpandable(&str[*j], lim);
	if (str[*j] && (str[*j] == DQUOTES || str[*j] == SQUOTES))
	{
		++(*j);
		lim = (lim) ? lim - 1 : 0;
	}
	q_lst->token = dupbtwqlim(&str[*j], lim - 1);
	while (lim)
	{
		++(*j);
		--lim;
	}
	++(*i);
	q_lst->next = NULL;
	if (g_quoted)
		setquotenod(q_lst);
	else
		g_quoted = q_lst;
	return (0);
}

static int	token_reconstitutor(char *str, int k)
{
	int	i;
	int	j;
	int	lim;

	i = 0;
	j = 0;
	lim = 0;
	if ((str[j] && (str[j] != DQUOTES && str[j] != SQUOTES))
	|| k == 0)
		token_starter(str, &j, &i);
	while (i < k)
		token_concatenator(str, &j, &i, lim);
	return (0);
}

char		*token_quotes_generator(char *str)
{
	int	k;

	k = counter_quoted_words(str);
	token_reconstitutor(str, k);
	return (str);
}
