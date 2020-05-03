/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_bslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/04 16:42:04 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

char			*dupbtwqlim(char *str, int lim)
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

char			*dupbtwq(char *str)
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

char			*ft_getbtw(char *tokens, int type)
{
	if (type == MATHS_EXP)
		return (ft_strdup(&(tokens[maths_len(tokens) + 2])));
	if (*tokens != DOLLAR)
		return (NULL);
	if (*tokens == DOLLAR && (*(tokens + 1) == SLASH
	|| *(tokens + 1) == SPC || !*(tokens + 1)))
		return (ft_strdup(tokens));
	while (*tokens && (*tokens == DOLLAR || *tokens == OP_BRACE
	|| *tokens == STAR || *tokens == AROB || *tokens == SHARP
	|| *tokens == WHY || *tokens == DASH || *tokens == EXCLAM))
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
