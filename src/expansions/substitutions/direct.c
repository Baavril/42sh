/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/08 17:43:17 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "builtins.h"
#include "libft.h"
#include "expansions.h"
#include "shell_variables.h"

extern struct s_svar	*g_svar;
extern char				*g_bgpid;

static int				get_pos_params(char **token)
{
	if (*(*token + 1) == SHARP)
	{
		count_pos_params(token);
		return (SUCCESS);
	}
	else if (ft_isdigit(*(*token + 1)))
	{
		reach_pos_params(token);
		return (SUCCESS);
	}
	else if (*(*token + 1) == WHY)
	{
		ret_value(token);
		return (SUCCESS);
	}
	return (ERROR);
}

static int				tak_pos_params(char **token)
{
	if (*(*token + 1) == DASH)
	{
		ft_strdel(token);
		*token = ft_strdup(EMPTY_STR);
		return (SUCCESS);
	}
	else if (*(*token + 1) == DOLLAR)
	{
		ft_strdel(token);
		*token = get_var_value("PID");
		return (SUCCESS);
	}
	return (ERROR);
}

static int				positional_params(char **token)
{
	if (*(*token + 1) == STAR || *(*token + 1) == AROB)
	{
		if (view_pos_param(token) == SUCCESS)
			return (SUCCESS);
	}
	else if (*(*token + 1) == EXCLAM)
	{
		ft_strdel(token);
		if (!(*token = ft_strdup((g_bgpid) ? g_bgpid : EMPTY_STR)))
			return (0);
		return (SUCCESS);
	}
	else if (get_pos_params(token) == SUCCESS)
		return (SUCCESS);
	else if (tak_pos_params(token) == SUCCESS)
		return (SUCCESS);
	return (ERROR);
}

static int				special_params(char **token)
{
	if (script_param(token) == SUCCESS)
		return (SUCCESS);
	if (positional_params(token) == SUCCESS)
		return (SUCCESS);
	return (ERROR);
}

int						direct_exp(char **token)
{
	struct s_svar	*tmp;

	tmp = g_svar;
	if (special_params(token) == SUCCESS)
		return (SUCCESS);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 1, ft_strlen(g_svar->key) - 1) == 0
				&& check_next_var(g_svar->key, token, 0) == SUCCESS)
		{
			ft_strdel(token);
			if (!(*token = ft_strdup(g_svar->value)))
				return (ERROR);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	if (!(*token = ft_strdup(EMPTY_STR)))
		return (ERROR);
	g_svar = tmp;
	return (SUCCESS);
}
