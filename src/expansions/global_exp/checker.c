/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_checker.c                               :+:      :+:    :+:   */
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

int		check_braces(char *token)
{
	int	i;

	i = 0;
	if (token[i] == OP_BRACE)
	{
		while (token[i])
		{
			if (token[i] == CL_BRACE)
				return (SIMPLE_EXP);
			++i;
		}
	}
	return (DIRECT_EXP);
}

int		check_colon(char *token)
{
	if (ft_strchr(token, COLON))
		return (COMPLEX_EXP);
	return (SIMPLE_EXP);
}

int		check_symbol(char *token)
{
	int		i;
	char	*symbol;

	i = 1;
	symbol = NULL;
	if (token[i] == SHARP && ft_isprint(token[i + 1]))
		return (BSHARP_EXP);
	if ((symbol = ft_strchr(token, SHARP)))
	{
		if (symbol[1] == SHARP && ft_isprint(symbol[2]))
			return (DSHARP_EXP);
		return (OSHARP_EXP);
	}
	if ((symbol = ft_strchr(token, PERCENT)))
	{
		if (symbol[1] == PERCENT && ft_isprint(symbol[2]))
			return (DPERCENT_EXP);
		return (OPERCENT_EXP);
	}
	return (SIMPLE_EXP);
}

int		check_colon_symbol(char *token)
{
	int	i;

	i = 0;
	while (token[i] != COLON)
		++i;
	++i;
	if (token[i] == WHY)
		return (WHY_EXP);
	if (token[i] == PLUS)
		return (PLUS_EXP);
	if (token[i] == DASH)
		return (DASH_EXP);
	if (token[i] == EQUAL)
		return (EQUAL_EXP);
	return (SIMPLE_EXP);
}

int		check_maths(char *token)
{
	int		i;
	int		opar;

	i = 2;
	opar = 0;
	if (!(token[0] == OP_PAR && token[1] == OP_PAR))
		return (ERROR);
	while (token[i])
	{
		if (token[i] == OP_PAR)
			opar++;
		if ((token[i] == CL_PAR && token[i + 1] == CL_PAR) && !opar)
			return (MATHS_EXP);
		if (token[i] == CL_PAR)
			opar--;
		if (opar < 0)
			return (ERROR);// parentheses imbriquees
		++i;
	}
	return (ERROR);
}
