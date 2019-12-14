/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/09 11:47:27 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "expansions.h"
#include "libft.h"

t_symexp	g_symexp[] =
{
	{DIRECT_EXP, &direct_exp},
	{SIMPLE_EXP, &simple_exp},
	{WHY_EXP, &why_exp},
	{PLUS_EXP, &plus_exp},
	{DASH_EXP, &dash_exp},
	{EQUAL_EXP, &equal_exp},
	{BSHARP_EXP, &bsharp_exp},
	{OSHARP_EXP, &osharp_exp},
	{DSHARP_EXP, &dsharp_exp},
	{OPERCENT_EXP, &opercent_exp},
	{DPERCENT_EXP, &dpercent_exp},
	{0, NULL}
};

static int		check_braces(char *token)
{
	int len;;

	len = ft_strlen(token) - 1;
	if (token[0] == OP_BRACE && token[len] == CL_BRACE)
		return (SIMPLE_EXP);
	return (DIRECT_EXP);
}

static int		check_colon(char *token)
{
	if (ft_strchr(token, COLON))
		return (COMPLEX_EXP);
	return (SIMPLE_EXP);
}

static int		check_symbol(char *token)
{
	int i;
	char *symbol;

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

static int		check_colon_symbol(char *token)
{
	int i;

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

static int		identifier(char *token)
{
	int i;

	i = 1;
	if (token[0] == DOLLAR)
	{
		while (token[i])
		{
			if (check_braces(&token[i]) == SIMPLE_EXP)
			{
				if (check_colon(&token[i]) == COMPLEX_EXP)
					return (check_colon_symbol(&token[i]));
				return (check_symbol(&token[i]));
			}
			i++;
		}
		return (DIRECT_EXP);
	}
	return (ERROR);
}

int		expansions_management(char **tokens)
{
	int i;
	int j;
	int type;
	
	i = 0;
	while (tokens[i])
	{
		j = 0;
		type = identifier(tokens[i]);
		ft_printf("%d\n", type);
		while (g_symexp[j].expand)
		{
			if (g_symexp[j].sym == type)
				g_symexp[j].expand(&tokens[i]);
			++j;
		}
		++i;
	}
	while (*tokens)
		ft_putendl(*tokens++);
	return (SUCCESS);
}
