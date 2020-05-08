/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:43:54 by baavril           #+#    #+#             */
/*   Updated: 2020/03/07 16:43:56 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_variables.h"
#include "expansions.h"

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
	{DSHARP_EXP, &osharp_exp},
	{OPERCENT_EXP, &opercent_exp},
	{DPERCENT_EXP, &opercent_exp},
	{MATHS_EXP, &maths_exp},
	{0, NULL}
};

int	expansions_launcher(t_expand *vars, int expand)
{
	vars->j = 0;
	if (!(expand) && ((vars->nb = ft_back_slashed(vars->tokens)) >= 0))
	{
		*(vars->tokens) = ft_set_slashed(vars->tokens);
		vars->type = identifier(*(vars->tokens));
		vars->btw = getbtw(*(vars->tokens), vars->type, 0);
		while (g_symexp[vars->j].expand)
		{
			if (g_symexp[vars->j].sym == vars->type)
				if (g_symexp[vars->j].expand(vars->tokens) == ERROR)
					return (ERROR);
			vars->j++;
		}
		if (vars->nb > 0)
			*(vars->tokens) = ft_setbslash(*(vars->tokens), vars->nb);
	}
	else
		*(vars->tokens) = ft_set_slashed(vars->tokens);
	return (SUCCESS);
}
