/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_pattern_matching.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/01/26 20:00:26 by bprunev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "globing.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int	pattern_id(t_pattern *var, char *match)
{
	if (var->j == 0 && ft_isalnum(match[var->j]))
		var->x = 1;
	else if (match[var->j] == OP_SQUAR
	&& match[ft_strpchr(&match[var->j], CL_SQUAR) + 1] == STAR)
	{
		var->x = 2;
		var->s = 1;
	}
	else if (match[var->j] == WHY)
	{
		var->x = 3;
		var->w = 1;
	}
	else if (match[var->j] == STAR)
		var->x = 4;
	return (SUCCESS);
}

int			complex_pattern_matching(t_pattern *var, char *match, char *str)
{
	while (var->j < var->len_m && match[var->j])
	{
		pattern_id(var, match);
		if (var->x)
		{
			matching_patterns(var, match, str);
			var->x = 0;
		}
		else
		{
			match_cmp(var, match, str);
			var->n = var->i;
		}
	}
	var->n = var->i;
	return (SUCCESS);
}
