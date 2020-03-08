/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:17:00 by baavril           #+#    #+#             */
/*   Updated: 2020/03/08 18:23:23 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "builtins.h"
#include "libft.h"
#include "expansions.h"
#include "shell_variables.h"

extern struct s_pos		*g_pos;

int						script_param(char **token)
{
	char	*tmp1;
	char	*tmp2;
	int		len;

	tmp1 = NULL;
	tmp2 = NULL;
	len = ft_strlen(*token);
	if (*(*token + 1) == '0')
	{
		if (ft_isin(SLASH, *token))
			len = ft_strpchr(*token, SLASH);
		if (ft_isin('"', *token))
			len = ft_strpchr(*token, '"');
		tmp1 = ft_strdup("42sh");
		tmp2 = ft_strndup(&(*token)[ft_strpchr(*token, '0') + 1], len - 2);
		ft_strdel(token);
		*token = ft_strjoin(tmp1, tmp2);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		return (SUCCESS);
	}
	return (ERROR);
}

static void				init_param_vars(t_params *vars)
{
	vars->len = 0;
	vars->esc = NULL;
	vars->tmp1 = NULL;
	vars->tmp2 = NULL;
	vars->tmp3 = NULL;
	vars->tmp4 = NULL;
}

static int				expand_pos_params(t_params *vars, char **token)
{
	struct s_pos	*ptr;

	if (*(*token + 1) == STAR && *(*token + 2) == '"')
	{
		ft_strdel(&vars->esc);
		if (!(vars->esc = get_var_value("IFS=")))
			vars->esc = ft_strdup(" ");
	}
	ptr = g_pos;
	while (g_pos && g_pos->next)
	{
		vars->tmp1 = ft_strdup(g_pos->value);
		vars->tmp4 = (vars->tmp2) ? NULL : ft_strjoin(vars->tmp1, vars->esc);
		vars->tmp3 = (vars->tmp2) ? vars->tmp2 : vars->tmp4;
		vars->tmp2 = ft_strjoin(vars->tmp3, g_pos->next->value);
		vars->tmp4 = vars->tmp2;
		vars->tmp2 = ft_strjoin(vars->tmp4, vars->esc);
		g_pos = g_pos->next;
		ft_strdel(&vars->tmp1);
		ft_strdel(&vars->tmp3);
		ft_strdel(&vars->tmp4);
	}
	g_pos = ptr;
	return (SUCCESS);
}

static int				substitute_pos_params(t_params *vars, char **token)
{
	if (vars->tmp2)
	{
		if (ft_isin(SLASH, *token))
			vars->len = ft_strpchr(*token, SLASH);
		if (ft_isin('"', *token))
			vars->len = ft_strpchr(*token, '"');
		vars->tmp1 = (*(*token + 1) == STAR)
		? ft_strndup(&(*token)[ft_strpchr(*token, STAR) + 1], vars->len - 2)
		: ft_strndup(&(*token)[ft_strpchr(*token, AROB) + 1], vars->len - 2);
		ft_strdel(token);
		if (!ft_isspace(vars->esc[0]))
		{
			vars->tmp3 = ft_strndup(vars->tmp2, ft_strlen(vars->tmp2) - 1);
			ft_strdel(&vars->tmp2);
			vars->tmp2 = vars->tmp3;
		}
		*token = ft_strjoin(vars->tmp2, vars->tmp1);
		ft_strdel(&vars->tmp1);
		ft_strdel(&vars->tmp2);
	}
	return (SUCCESS);
}

int						view_pos_param(char **token)
{
	t_params		vars;

	init_param_vars(&vars);
	vars.esc = ft_strdup(" ");
	vars.len = ft_strlen(*token);
	if (!g_pos)
		return (ERROR);
	expand_pos_params(&vars, token);
	substitute_pos_params(&vars, token);
	ft_strdel(&vars.esc);
	return (SUCCESS);
}
