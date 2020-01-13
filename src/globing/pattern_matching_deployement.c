/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_deployement.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 13:58:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int
	deployement_support(t_glob *var, char *str, char *match, int flag)
{
	if (ft_strpchr(&match[var->i + var->x], CL_SQUAR) > 0
	&& check_deploy(&str[var->i]
	, &match[var->i + var->x], flag, 0) >= SUCCESS)
	{
		var->x += ft_strpchr(&match[var->i + var->x], CL_SQUAR);
		var->diff -= 1;
	}
	return (SUCCESS);
}

int
	reach_star_flag(t_glob *var, char *match, char *str, int flag)
{
	while (match[var->i + var->x] && match[var->i + var->x] != STAR)
	{
		if (var->i <= (int)ft_strlen(str)
		&& match[var->i + var->x] != str[var->i])
		{
			if (match[var->i + var->x] == WHY
			&& str[var->i] && ft_isprint(str[var->i]))
				var->diff -= 1;
			else if (match[var->i + var->x] == OP_SQUAR)
				deployement_support(var, str, match, flag);
			var->diff += 1;
		}
		++var->i;
	}
	var->j = var->i + var->x;
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
		++var->i;
	if (var->c == ERROR)
		var->diff += 1;
	var->x += ft_strpchr(&match[var->i + var->x], CL_SQUAR) + 1;
	var->j += ft_strpchr(&match[var->j], CL_SQUAR);
	if (flag >= 2 && !match[var->j + 1])
		++var->i;
	return (SUCCESS);
}
