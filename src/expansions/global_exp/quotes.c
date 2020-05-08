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

static int		reachquotelim(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != c)
	{
		++i;
		if (str[i] == c && str[i - 1] == BSLASH)
			++i;
	}
	++i;
	return (i);
}

int				getquotelim(char *str)
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

int				counter_quoted_words(char *str)
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

void			setquotenod(struct s_quoted *new_back)
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

int				isexpandable(char *str, int lim)
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
