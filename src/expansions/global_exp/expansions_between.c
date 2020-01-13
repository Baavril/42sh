/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_bslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 18:31:11 by tgouedar         ###   ########.fr       */
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

static char	*ft_btwquotes(char *tokens, int c, int d)
{
	char	*ret;

	ret = NULL;
	if (c > d)
	{
		if (!(ret = (char*)ft_memalloc(sizeof(char) * (c - d + 1))))
			return (NULL);
	}
	else
	{
		if (!(ret = (char*)ft_memalloc(sizeof(char) * (d - c + 1))))
			return (NULL);
	}
	c = 0;
	d = 0;
	while (*(tokens + c))
	{
		if (*(tokens + c) == DQUOTES)
			c++;
		else
			ret[d++] = *(tokens + c++);
	}
	return (ret);
}

char		*ft_quoted(char *tokens)
{
	int	c;
	int	d;

	c = 0;
	d = 0;
	while (*tokens && *tokens != DQUOTES)
		tokens++;
	tokens++;
	while (*(tokens + c))
	{
		if (*(tokens + c) == DQUOTES)
			d++;
		c++;
	}
	return (ft_btwquotes(tokens, c, d));
}

char	*ft_getbtw(char *tokens, int type)
{
	if (type == MATHS_EXP)
		return (ft_strdup(&(tokens[maths_len(tokens) + 2])));
	if (*tokens != DOLLAR)
		return (NULL);
	if (*tokens == DOLLAR && (*(tokens + 1) == SLASH
	|| *(tokens + 1) == SPC || !*(tokens + 1)))
		return (ft_strdup(tokens));
	if (ft_isin(DQUOTES, tokens))
		return (ft_quoted(tokens));
	while (*tokens && (*tokens == DOLLAR || *tokens == OP_BRACE))
		tokens++;
	while (type == DIRECT_EXP && *tokens && (ft_isalpha(*tokens)
	|| ft_isdigit(*tokens) || *tokens == AMPER || *tokens == UNDERSCORE))
		tokens++;
	while (type != DIRECT_EXP && *tokens && *tokens != CL_BRACE)
	{
		tokens++;
		if (*(tokens + 1) == AMPER)
			++tokens;
	}
	if (*tokens == CL_BRACE)
		++tokens;
	//if (*tokens == BSLASH)
	//	tokens++;
	return (ft_strdup(tokens));
}
