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
#include "builtin_test.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

struct s_quoted	*g_quoted;

static int reachquotelim(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != c)
		++i;
	++i;
	return (i);
}

static int	getquotelim(char *str)
{
	int	i;

	i = 0;
	if (str[i] == DQUOTES)
		return (reachquotelim(&str[i], DQUOTES));
	else if (str[i] == SQUOTES)
		return (reachquotelim(&str[i], SQUOTES));
	else if (str[i] != SQUOTES && str[i] != DQUOTES)
	{
		++i;
		while (str[i] && str[i] != DQUOTES && str[i] != SQUOTES)
			++i;
		return (i);
	}
	return (i);
}

static int	counter_quoted_words(char *str)
{
	int	i;
	int	k;
	int	len;

	i = 0;
	k = 0;
	len = (int)ft_strlen(str);
	while (i < len && str[i])
	{
		i += getquotelim(&str[i]);
		++k;
	}
	return (k);
}

void		setquotenod(struct s_quoted *new_back)
{
	struct s_quoted	*voyager;

	if (!g_quoted)
		return ;
	else
	{
		voyager = g_quoted;
		while (voyager->next)
			voyager = voyager->next;
		voyager->next = new_back;
	}
}

static int	isexpandable(char *str, int lim)
{
	int		i;
	int		exp;

	i = 0;
	exp = 0;
	while (i < lim)
	{
		if (str[i] == DQUOTES)
		{
			++i;
			while (str[i] && str[i] != DQUOTES)
				++i;
		}
		if (str[i] == SQUOTES)
		{
			++i;
			if ((str[i] != SQUOTES && str[i] != DQUOTES) || (str[i] == DQUOTES
			&& (str[i + 1] != SQUOTES && str[i + 1] != DQUOTES)))
				exp = 1;
			while (str[i] != SQUOTES && str[i])
				++i;
		}
		++i;
	}
	return (exp);
}

static char	*dupbtwqlim(char *str, int lim)
{
	int		i;
	char	*ret;

	i = 0;
	if (lim > 1 && str[lim] != DQUOTES && str[lim] != SQUOTES)
		++lim;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * (lim + 2))))
		return (NULL);
	while (i < lim && str[i])
	{
		ret[i] = str[i];
		++i;
	}
	return (ret);
}

static char	*dupbtwq(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i] && (str[i] != DQUOTES && str[i] != SQUOTES))
		++i;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] && (str[i] != DQUOTES && str[i] != SQUOTES))
	{
		ret[i] = str[i];
		++i;
	}
	return (ret);
}

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
