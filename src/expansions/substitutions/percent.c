/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/08 14:50:11 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

extern struct s_svar	*g_svar;

static void				init_rev_vars(t_rev *vars)
{
	vars->i = 0;
	vars->len = 0;
	vars->flag = 0;
	vars->tmp1 = NULL;
}

static int				check_percent_var(char **token, char *word,
										struct s_svar *tmp, int flag)
{
	char	*value;

	value = NULL;
	if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
	&& check_next_var(g_svar->key, token, 1) == SUCCESS)
	{
		free(*token);
		if (!(value = ft_strdup(g_svar->value)))
			return (ERROR);
		*token = ft_strdup(matching_ret(ft_strrev(value), word, flag));
		*token = ft_strrev(*token);
		g_svar = tmp;
		ft_strdel(&word);
		ft_strdel(&value);
		return (SUCCESS);
	}
	return (ERROR);
}

static int				revhelper(char *word, t_rev *vars)
{
	while (word[vars->len] == CL_SQUAR)
	{
		while (word[vars->len] != OP_SQUAR)
			--vars->len;
		while (word[vars->len] != CL_SQUAR)
		{
			vars->tmp1[vars->i] = word[vars->len];
			++vars->i;
			++vars->len;
		}
		vars->tmp1[vars->i] = word[vars->len];
		while (word[vars->len] != OP_SQUAR)
			--vars->len;
		if (vars->len > 0)
		{
			--vars->len;
			++vars->i;
		}
		else if (vars->len == 0 && word[vars->len] == OP_SQUAR)
			vars->flag++;
	}
	return (SUCCESS);
}

static char				*revstar(char *word)
{
	t_rev	vars;

	init_rev_vars(&vars);
	vars.len = (int)ft_strlen(word) - 1;
	if (!(vars.tmp1 = (char*)ft_memalloc(sizeof(char) * (vars.len + 2))))
		return (NULL);
	while (vars.len >= 0)
	{
		revhelper(word, &vars);
		if (vars.flag)
			break ;
		vars.tmp1[vars.i] = word[vars.len];
		++vars.i;
		--vars.len;
	}
	ft_strdel(&word);
	return (vars.tmp1);
}

int						opercent_exp(char **token)
{
	int				flag;
	char			*word;
	struct s_svar	*tmp;

	tmp = g_svar;
	flag = (!(ft_spechrlen(*token))) ? 2 : 1;
	word = ft_strcdup(ft_strchr(*token, PERCENT) + flag, CL_BRACE);
	if (ft_isin(OP_SQUAR, word) && ft_isin(CL_SQUAR, word))
		word = revstar(word);
	else
		ft_strrev(word);
	while (g_svar)
	{
		if (check_percent_var(token, word, tmp, flag) == SUCCESS)
			return (SUCCESS);
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	if (!(*token = ft_strdup(EMPTY_STR)))
		return (ERROR);
	g_svar = tmp;
	ft_strdel(&word);
	return (SUCCESS);
}
