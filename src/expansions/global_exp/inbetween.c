/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_bslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/03/01 12:09:58 by tgouedar         ###   ########.fr       */
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
