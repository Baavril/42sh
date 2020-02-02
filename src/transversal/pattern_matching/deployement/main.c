/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deploy_pattern_matching.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/02/02 18:11:15 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "globing.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

int	islast(t_pattern *var, char *str, char c)
{
	if (ft_isprint(c))
	{
		while (str[var->i])
			++var->i;
		while (str[var->i] != var->c)
			--var->i;
		++var->i;
	}
	return (SUCCESS);
}

int	deployement_support(t_pattern *var, char *str, char *match)
{
	if (ft_strpchr(&match[var->j], CL_SQUAR) > 0
	&& check_deploy(&str[var->i]
	, &match[var->j], var->flag, var) > SUCCESS)
	{
		var->j += ft_strpchr(&match[var->j], CL_SQUAR);
		var->diff -= 1;
		return (SUCCESS);
	}
	else if (var->s)
	{
		if (var->i >= var->len_s)
		{
			var->diff++;
			var->i = var->len_s - 1;
			return (ERROR);
		}
		++var->i;
		deployement_support(var, str, match);
	}
	return (ERROR);
}

int	deployement_limit(t_pattern *var, char *match, char *str)
{
	int	tmp;

	tmp = 0;
	var->c = check_deploy(&str[var->i], &match[var->j], var->flag, var);
	islast(var, str, var->c);
	if (var->c == ERROR)
		var->diff += 1;
	var->j += ft_strpchr(&match[var->j], CL_SQUAR) + 1;
	tmp = var->j;
	if (var->j < var->len_m && match[var->j] == STAR)
		++tmp;
	while (var->j < var->len_m && ft_isalnum(match[tmp])
	&& match[tmp] != str[var->i] && var->i > 0)
		--var->i;
	return (SUCCESS);
}
