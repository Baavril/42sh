/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_program.c                         :+:      :+:    :+:   */
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
	matching_simple_pattern(t_glob *var, char *match, char *str)
{
	while (var->i < var->len_s && str[var->i] != match[var->j])
	{
		++var->i;
		if (str[var->i] == match[var->j])
		{
			if (ft_isin(match[var->j], &str[var->i + 1]))
				++var->i;
		}
	}
	if (var->s)
	{
		var->i = var->len_s;
		while (var->i >= 0 && match[var->j] != str[var->i])
			--var->i;
		var->s = 0;
	}
	if (var->i < var->len_s && match[var->j] == str[var->i])
		++var->i;
	else
		var->diff += 1;
	++var->j;
	return (SUCCESS);
}

static int
	matching_tracker(t_glob *var, char *match, char *str)
{
	while (match[var->j] && match[var->j] == STAR)
		++var->j;
	if (match[var->j] == OP_SQUAR)
		recursive_matching(var, match, str);
	else if (ft_isalnum(match[var->j]))
		matching_simple_pattern(var, match, str);
	else if (!match[var->j] && match[var->j - 1] == STAR && var->flag >= 2)
		var->i = var->len_s;
	return (SUCCESS);
}

static int
	matching_first_pattern(t_glob *var, char *match, char *str)
{
	if (match[var->j] == str[var->i])
		++var->i;
	else
		var->diff += 1;
	++var->j;
	if (!match[var->j] && var->flag >= 2)
		var->i = var->len_s;
	return (SUCCESS);
}

int
	matching_patterns(t_glob *var, char *match, char *str)
{
	if (var->x == 1)
		matching_first_pattern(var, match, str);
	if (var->x == 2)
	{
		deployement_limit(var, match, str);
		var->s = 1;
	}
	if (var->x == 3)
	{
		++var->i;
		++var->j;
		if (!match[var->j] && var->flag >= 2)
			var->i = var->len_s;
	}
	if (var->x == 4)
		matching_tracker(var, match, str);
	var->n = var->i;
	return (SUCCESS);
}
