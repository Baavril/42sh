/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/04 16:41:17 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

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

static void	initexpvars(t_expand *vars)
{
	vars->j = 0;
	vars->nb = 0;
	vars->type = 0;
	vars->tmp = NULL;
	vars->ptm = NULL;
	vars->btw = NULL;
	vars->keep = NULL;
	vars->tokens = NULL;
}

static int	expansions_linker(t_expand *vars)
{
	if (*(vars->tokens))
	{
		if (vars->tmp == NULL)
			vars->tmp = ft_strdup(*(vars->tokens));
		else
		{
			vars->ptm = ft_strdup(vars->tmp);
			ft_strdel(&(vars->tmp));
			vars->tmp = ft_strjoin(vars->ptm, *(vars->tokens));
			ft_strdel(&(vars->ptm));
		}
	}
	if (vars->btw)
	{
		if (ft_strlen(*(vars->tokens)) == 0 && vars->type == WHY_EXP)
			ft_strdel(&vars->btw);
		else
		{
			if (vars->tmp == NULL)
				vars->tmp = vars->btw;
			else
			{
				vars->ptm = ft_strdup(vars->tmp);
				ft_strdel(&(vars->tmp));
				vars->tmp = ft_strjoin(vars->ptm, vars->btw);
				ft_strdel(&(vars->ptm));
				ft_strdel(&vars->btw);
			}
		}
	}
	return (SUCCESS);
}

static int	expansions_launcher(t_expand *vars)
{
	vars->j = 0;
	if (((vars->nb = ft_back_slashed(vars->tokens)) >= 0)
	&& !(ft_isin(SQUOTES, *vars->tokens) && ft_isin(DOLLAR, *vars->tokens)))
	{
		*(vars->tokens) = ft_set_slashed(vars->tokens);
		*(vars->tokens) = ft_isin(SQUOTES, *vars->tokens)
		? ft_unset_quoted(*vars->tokens, SQUOTES)
		: ft_unset_quoted(*vars->tokens, DQUOTES);
		vars->type = identifier(*(vars->tokens));
		vars->btw = ft_getbtw(*(vars->tokens), vars->type);
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
	{
		*(vars->tokens) = ft_set_slashed(vars->tokens);
		*(vars->tokens) = ft_unset_quoted(*vars->tokens, SQUOTES);
	}
	return (SUCCESS);
}

static char	*expansions_management(char **splitok)
{
	t_expand	vars;

	initexpvars(&vars);
	vars.tokens = splitok;
	while (*(vars.tokens))
	{
		if (expansions_launcher(&vars) == ERROR)
		{
			ft_dprintf(2, "42sh: %s: bad substitution\n", *vars.tokens);
			ft_tabdel(&splitok);
			ft_strdel(&vars.btw);
			ft_strdel(&vars.tmp);
			return (NULL);
		}
		expansions_linker(&vars);
		vars.tokens++;
	}
	ft_tabdel(&splitok);
	return (vars.tmp);
}

int			expansions_treatment(char **tokens)
{
	char **splitok;

	if (**tokens == TILDE)
		tilde_exp(tokens);
	if (!(splitok = ft_expsplit(*tokens, DOLLAR)))
		return (ERROR);
	ft_strdel(tokens);
	*tokens = expansions_management(splitok);
	return (SUCCESS);
}
