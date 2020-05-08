/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:40:47 by baavril           #+#    #+#             */
/*   Updated: 2020/03/07 16:42:03 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"

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

static int	expansions_linker_btw(t_expand *vars)
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
	return (SUCCESS);
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
		expansions_linker_btw(vars);
	return (SUCCESS);
}

char		*expansions_management(char **splitok, int expand)
{
	int			i;
	int			lim;
	t_expand	vars;

	i = 0;
	initexpvars(&vars);
	lim = ft_tablen(splitok);
	vars.tokens = splitok;
	while (i < lim)
	{
		if (expansions_launcher(&vars, expand) == ERROR)
		{
			ft_dprintf(2, "42sh: %s: bad substitution", *vars.tokens);
			ft_tabdel(&splitok);
			ft_strdel(&vars.btw);
			ft_strdel(&vars.tmp);
			return (ft_strdup(EMPTY_STR));
		}
		expansions_linker(&vars);
		++vars.tokens;
		++i;
	}
	ft_tabdel(&splitok);
	return (vars.tmp);
}
