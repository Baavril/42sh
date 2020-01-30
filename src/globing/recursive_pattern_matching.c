/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_pattern_matching.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/26 20:00:26 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int
	reach_limit(t_glob *var, char *str)
{
	while (ft_isprint(var->c) && str[var->i] != var->c)
	{
		++var->i;
		if (ft_isin(var->c, &str[var->i + 1]))
			++var->i;
	}
	return (SUCCESS);
}

static int
	recursive_searcher(t_glob *var, char *match, char *str, int flag)
{
	if ((var->c = check_deploy(&str[var->i], &match[var->j], 1, var)) > SUCCESS)
	{
		reach_limit(var, str);
		if (ft_isprint(var->c) && var->c == str[var->i])
			++var->i;
		if ((flag == 0 && check_deploy(&str[var->i], &match[var->j
		+ ft_strpchr(&match[var->j], CL_SQUAR) + 1], 1, var) > SUCCESS)
		|| (flag == 1
		&& check_deploy(&str[var->i], &match[ft_strpchr(match, CL_SQUAR)
		+ ft_strpchr(&match[ft_strpchr(match, CL_SQUAR) + 1],
		OP_SQUAR) + 1], 1, var) > SUCCESS))
		{
			var->j += ft_strpchr(&match[var->j], CL_SQUAR) + 1;
			return (SUCCESS);
		}
		else
		{
			var->i = var->k;
			++var->i;
			recursive_matching(var, match, str);
		}
	}
	return (ERROR);
}

int
	recursive_matching(t_glob *var, char *match, char *str)
{
	var->k = var->i;
	if (match[var->j + ft_strpchr(&match[var->j], CL_SQUAR) + 1] == OP_SQUAR)
		recursive_searcher(var, match, str, 0);
	else if (var->flag == 2
	&& var->j + ft_strpchr(&match[var->j], CL_SQUAR)
	+ ft_strpchr(&match[ft_strpchr(&match[var->j], CL_SQUAR) + 1],
	OP_SQUAR) - 1 < var->len_m
	&& match[var->j + ft_strpchr(&match[var->j], CL_SQUAR)
	+ ft_strpchr(&match[ft_strpchr(&match[var->j], CL_SQUAR) + 1],
	OP_SQUAR) - 1] == OP_SQUAR)
		recursive_searcher(var, match, str, 1);
	else if (var->flag == 1)
	{
		var->s = 1;
		match_cmp(var, match, str);
	}
	else if (var->flag >= 2)
		deployement_limit(var, match, str);
	return (SUCCESS);
}
