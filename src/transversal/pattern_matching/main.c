/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/26 20:00:26 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "globing.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static void	init_pattern_vars(t_pattern *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->n = 0;
	vars->x = 0;
	vars->w = 0;
	vars->s = 0;
	vars->c = 0;
	vars->k = 0;
	vars->len_s = 0;
	vars->len_m = 0;
	vars->diff = 0;
}

char		*pattern_matching(char *str, char *match, int flag)
{
	t_pattern	var;

	init_pattern_vars(&var);
	var.len_s = ft_strlen(str);
	var.len_m = ft_strlen(match);
	var.flag = flag;
	if (!ft_isin(STAR, match))
		simple_pattern_matching(&var, match, str);
	else
		complex_pattern_matching(&var, match, str);
	if (var.flag == 2 && !var.diff)
		return (&str[var.i]);
	else if (var.flag == 1 && !var.diff)
		return ((var.n != 0) ? &str[var.n] : str);
	else if (var.flag == 3)
		return (((var.len_s != var.i) || var.diff) ? EMPTY_STR : str);
	return (str);
}

char		*matching_ret(char *token, char *match, int flag)
{
	char *ret;

	ret = NULL;
	if (!match || !*match)
		ret = token;
	else
		ret = pattern_matching(token, match, flag);
	return (ret);
}
