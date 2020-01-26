/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_deployement.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/26 19:59:30 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int
	deployement_support(t_glob *var, char *str, char *match, int flag)
{
	if (ft_strpchr(&match[var->j], CL_SQUAR) > 0
	&& check_deploy(&str[var->i]
	, &match[var->j], flag, 0) >= SUCCESS)
	{
		var->j += ft_strpchr(&match[var->j], CL_SQUAR);
		var->diff -= 1;
	}
	return (SUCCESS);
}

int
	reach_star_flag(t_glob *var, char *match, char *str, int flag)
{
	while (var->j < (int)ft_strlen(match) && match[var->j] && match[var->j] != STAR)
	{
		if ((size_t)var->i <= ft_strlen(str)
		&& match[var->j] != str[var->i])
		{
			if (match[var->j] == WHY
			&& str[var->i] && ft_isprint(str[var->i]))
				var->diff -= 1;
			else if (match[var->j] == OP_SQUAR)
				deployement_support(var, str, match, flag);
			var->diff += 1;
		}
		++var->i;
		++var->j;
	}
	var->n = var->i;
	return (SUCCESS);
}

int
	star_no_deployement(t_glob *var, char *match, char *str, int flag)
{
	while (var->i <= (int)ft_strlen(str) && str[var->i]
	&& str[var->i] != match[var->j + 1])
	{
		++var->i;
		if (str[var->i] == match[var->j + 1])
		{
			if (flag >= 2 && ft_isin(match[var->j + 1], &str[var->i + 1]))
				++var->i;
		}
	}
	if (var->i <= (int)ft_strlen(str) && str[var->i] != match[var->j + 1])
		var->diff += 1;
	return (SUCCESS);
}

int
	star_deployement(t_glob *var, char *match, char *str, int flag)
{
	var->c = check_deploy(&str[var->i], &match[var->j + 1], flag, 1);
	while (ft_isprint(var->c) && str[var->i] != var->c)
	{
		if (var->j + 3 < (int)ft_strlen(&match[ft_strpchr(&match[var->j], CL_SQUAR)])
		&& str[var->i] == match[ft_strpchr(&match[var->j], CL_SQUAR) + 3])
			break ; 
		++var->i;
	}
	if (var->c == ERROR)
		var->diff += 1;
	var->j += ft_strpchr(&match[var->j], CL_SQUAR);
	if (flag == 1 && (size_t)var->i < ft_strlen(str) && ft_isin(OP_SQUAR, &match[var->j]) && str[var->i] == str[var->i + 1] && match[ft_strlen(match) - 1] == STAR)
		++var->i;
	if (flag >= 2 && !match[var->j + 1])
	{
		++var->i;
		if ((size_t)var->i < ft_strlen(str) && str[var->i] == str[var->i - 1])
			++var->i;
	}
	return (SUCCESS);
}
