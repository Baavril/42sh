/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
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

void	init_glob_vars(t_glob *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->n = 0;
	vars->x = 0;
	vars->c = 0;
	vars->diff = 0;
}

char	*pattern_matching(char *str, char *match, int flag)
{
	t_glob	var;

	init_glob_vars(&var);
	while (match[var.j])
	{
		reach_star_flag(&var, match, str, flag);
		fixing_star_flag(&var, match, str, flag);
		reach_next_star_flag(&var, match, str, flag);
		positionning_star_flag(&var, str, match);
		if (!match[var.j])
			break ;
		++var.j;
	}
	if (flag == 2 && !var.diff)
		return (&str[var.i]);
	else if (flag == 1 && !var.diff)
		return ((var.n != 0) ? &str[var.n] : str);
	else if (flag == 3)
		return ((((int)ft_strlen(str) != var.i)
		|| var.diff) ? EMPTY_STR : str);
	return (str);
}

char	*matching_ret(char *token, char *match, int flag)
{
	char *ret;

	ret = NULL;
	if (!match || !*match)
		ret = token;
	else
		ret = pattern_matching(token, match, flag);
	return (ret);
}
