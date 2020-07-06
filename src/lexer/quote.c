/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:28:12 by yberramd          #+#    #+#             */
/*   Updated: 2020/07/06 17:47:40 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int					ft_is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int			ft_is_op_bracket(char c)
{
	return (c == '(' || c == '{');
}

static char			val_quote_type(char *c)
{
	if (c[0] == '\'' || c[0] == '\"')
		return (c[0]);
	if (c[0] == '(')
	{
		if (c[1] == '(')
			return (-1);
		else
			return (')');
	}
	if (c[0] == '{')
	{
		if (c[1] == '{')
			return (-2);
		else
			return ('}');
	}
	return (-3);
}

static int			check_close_bracket(char *str, char quote_type)
{
	if (quote_type == -1 && str[0] == ')' && str[1] == ')')
		return (1);
	if (quote_type == -2 && str[0] == '}' && str[1] == '}')
		return (1);
	if (str[0] == quote_type)
		return (1);
	return (0);
}

void				ft_quote(char **s, int *i, char quote_t, _Bool open_q)
{
	while ((*s)[*i])
	{
		if (!open_q && (ft_is_quote((*s)[*i]) || ft_is_op_bracket((*s)[*i])))
		{
			open_q ^= 1;
			quote_t = val_quote_type(&(*s)[(*i)++]);
			if (quote_t == -1 || quote_t == -2)
				(*i)++;
			continue;
		}
		if (!open_q && (ft_istoken(&(*s)[*i]) || ft_isspace((*s)[*i])))
			break ;
		if (check_close_bracket(&(*s)[*i], quote_t))
		{
			++(*i);
			open_q ^= 1;
			if (quote_t == -1 || quote_t == -2)
				(*i)++;
			continue ;
		}
		if ((*s)[*i] == '\\' && ((*s)[*i + 1])
		&& ((open_q && quote_t != '\'') || !open_q))
			++(*i);
		++(*i);
	}
}
