/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_bslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/15 17:04:51 by baavril          ###   ########.fr       */
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

static char	*inquotes(char *tokens, char d)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (tokens[i + c] == d)
		++c;
	while (tokens[i + c] && tokens[i + c] != d)
		++i;
	return (ft_strndup(&tokens[c], i));
}

int		ft_strqchr(char *tokens, char c)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == c && tokens[i + 1] != c)
			return (i);
		i++;
	}
	return (i);
}

char		*ft_unset_quoted(char *tokens, char c)
{
	int	n;
	char	*tmp;
	char	*ptm;
	char	*keep;

	n = 0;
	tmp = NULL;
	ptm = NULL;
	keep = NULL;
	if (ft_isin(DOLLAR, tokens) && c == DQUOTES)
		return (tokens);
	while (ft_isin(c, &tokens[n]))
	{
		tmp = inquotes(&tokens[n], c);
		keep = ptm;
		ptm = (keep == NULL) ? ft_strdup(tmp) : ft_strjoin(keep, tmp);
		ft_strdel(&tmp);
		ft_strdel(&keep);
		n += 1;
		n += ft_strqchr(&tokens[n], c);
		if (n > (int)ft_strlen(tokens))
			break ;
	}
	if (n)
	{
		ft_strdel(&tokens);
		tokens = ptm;
	}
	return (tokens);
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
	while (*tokens && (*tokens == DOLLAR || *tokens == OP_BRACE || *tokens == STAR || *tokens == AROB || *tokens == SHARP))
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
	return (ft_strdup(tokens));
}
