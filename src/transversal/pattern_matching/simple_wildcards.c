/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_pattern_matching.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/02/02 18:50:15 by bprunev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "globing.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int
	automate_flags(t_pattern *var, char *match, char *str)
{
	if (var->w)
	{
		while (var->i < var->len_s && match[var->j] != str[var->i])
			++var->i;
		if (match[var->j] == str[var->i])
			var->diff -= 1;
		var->w = 0;
	}
	else if (var->s)
	{
		if (var->i == var->len_s)
		{
			while (var->i >= 0 && match[var->j] != str[var->i])
				--var->i;
			var->s = 0;
		}
		else if (var->i < var->len_s)
		{
			while (var->i < var->len_s && match[var->j] != str[var->i])
				++var->i;
			var->s = 0;
		}
		--var->diff;
	}
	return (SUCCESS);
}

int
	match_cmp(t_pattern *var, char *match, char *str)
{
	if ((var->i < var->len_s && var->i != -1 && match[var->j] != str[var->i])
		|| var->i >= var->len_s)
	{
		if (match[var->j] == WHY
		&& str[var->i] && ft_isprint(str[var->i]))
			var->diff -= 1;
		else if (match[var->j] == OP_SQUAR)
		{
			if (var->i < var->len_s)
				deployement_support(var, str, match);
		}
		else
			automate_flags(var, match, str);
		var->diff += 1;
	}
	++var->i;
	++var->j;
	return (SUCCESS);
}

int
	simple_pattern_matching(t_pattern *var, char *match, char *str)
{
	while (var->j < var->len_m && match[var->j])
	{
		match_cmp(var, match, str);
	}
	var->n = var->i;
	return (SUCCESS);
}
