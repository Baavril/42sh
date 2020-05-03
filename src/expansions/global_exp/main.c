/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/03/03 19:58:31 by yberramd         ###   ########.fr       */
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

struct s_quoted	*g_quoted;

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

static void	free_quoted_token_lst()
{
	struct s_quoted *tmp;

	while (g_quoted)
	{
		ft_strdel(&(g_quoted->token));
		tmp = g_quoted->next;
		free(g_quoted);
		g_quoted = tmp;
	}
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

static int	expansions_launcher(t_expand *vars, int expand)
{
	vars->j = 0;
	if (!(expand) && ((vars->nb = ft_back_slashed(vars->tokens)) >= 0))
	{
		*(vars->tokens) = ft_set_slashed(vars->tokens);
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
		*(vars->tokens) = ft_set_slashed(vars->tokens);
	return (SUCCESS);
}

static char	*expansions_management(char **splitok, int expand)
{
	t_expand	vars;

	initexpvars(&vars);
	vars.tokens = splitok;
	while (*(vars.tokens))
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
		vars.tokens++;
	}
	ft_tabdel(&splitok);
	return (vars.tmp);
}

static int	expansions_quoted_treatment(char **tokens, char **splitok)
{
	struct s_quoted	*tmp;
	char			*tmp_to_free;
	char			*tmp_to_free_2;
	
	token_quotes_generator(*tokens);
	tmp = g_quoted;
	ft_strdel(tokens);
	tmp_to_free = NULL;
	while (g_quoted)
	{
		if (!(splitok = ft_expsplit(g_quoted->token, DOLLAR)))
			return (ERROR);
		if (*tokens == NULL)
			*tokens = expansions_management(splitok, g_quoted->expand);
		else
		{
			tmp_to_free = ft_strdup(*tokens);
			ft_strdel(&(*tokens));
			tmp_to_free_2 = expansions_management(splitok, g_quoted->expand);
			*tokens = ft_strjoin(tmp_to_free, tmp_to_free_2);
			ft_strdel(&tmp_to_free);
			ft_strdel(&tmp_to_free_2);
		}
		g_quoted = g_quoted->next;
	}
	g_quoted = tmp;
	return (0);
}

int			expansions_treatment(char **tokens)
{
	char **splitok;

	splitok = NULL;
	if (**tokens == TILDE)
		tilde_exp(tokens);
	if (*tokens && (ft_isin(DQUOTES, *tokens) || ft_isin(SQUOTES, *tokens)))
	{
		expansions_quoted_treatment(tokens, splitok);
		free_quoted_token_lst();
	}
	else
	{
		if (!(splitok = ft_expsplit(*tokens, DOLLAR)))
			return (ERROR);
		ft_strdel(tokens);
		*tokens = expansions_management(splitok, 0);
	}
	return (SUCCESS);
}
