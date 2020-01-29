/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
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

void	init_glob_vars(t_glob *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->n = 0;
	vars->x = 0;
	vars->w = 0;
	vars->s = 0;
	vars->c = 0;
	vars->diff = 0;
}

static int
	deployement_support(t_glob *var, char *str, char *match, int flag)
{
	if (ft_strpchr(&match[var->j], CL_SQUAR) > 0
	&& check_deploy(&str[var->i]
	, &match[var->j], flag, var) > SUCCESS)
	{
		var->j += ft_strpchr(&match[var->j], CL_SQUAR);
		var->diff -= 1;
		return (SUCCESS);
	}
	else if (var->s)
	{
		if (var->i == (int)ft_strlen(str))
			var->diff++;
		++var->i;
		deployement_support(var, str, match, flag);
	}
	return (ERROR);
}

int
	match_id(t_glob *var, char *match, char *str, int flag)
{
	int	len_s;

	len_s = ft_strlen(str);
	if (match[var->j] != str[var->i])
	{
		if (match[var->j] == WHY
		&& str[var->i] && ft_isprint(str[var->i]))
			var->diff -= 1;
		else if (match[var->j] == OP_SQUAR)
		{
			deployement_support(var, str, match, flag);
				
			}
		else if (var->w)
		{
			while (var->i < len_s && match[var->j] != str[var->i])
				++var->i;
			if (match[var->j] == str[var->i])
				var->diff -= 1;
			var->w = 0;
		}
		else if (var->s)
		{
			if ((size_t)var->i == ft_strlen(str))
			{
				while (match[var->j] != str[var->i])
					--var->i;
				var->s = 0;
			}
			else if ((size_t)var->i < ft_strlen(str))
			{
				while (match[var->j] != str[var->i])
					++var->i;
				var->s = 0;
			}
			--var->diff;
		}
		var->diff += 1;
	}
	else if (var->i == len_s && ft_isprint(match[var->j]))
		var->diff += 1;
	++var->i;
	++var->j;
	return (SUCCESS);
}

int
	simple_pattern_matching(t_glob *var, char *match, char *str, int flag)
{
	int	len_m;

	len_m = ft_strlen(match);
	while (var->j < len_m && match[var->j])
	{
		match_id(var, match, str, flag);
	}
	var->n = var->i;
	return (SUCCESS);
}

int
	islast(t_glob *var, char *str, char c)
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

int
	deployement_limit(t_glob *var, char *match, char *str, int flag)
{
	var->c = check_deploy(&str[var->i], &match[var->j], flag, var);
	islast(var, str, var->c);
	if (var->c == ERROR)
		var->diff += 1;
	var->j += ft_strpchr(&match[var->j], CL_SQUAR) + 1;
	return (SUCCESS);
}

int
	backtracking_deployement(t_glob *var, char *match, char *str, int flag)
{
	int val;

	val = var->i;
	if (match[ft_strpchr(match, CL_SQUAR) + 1] == OP_SQUAR)
	{
		if ((var->c = check_deploy(&str[var->i], &match[var->j], 1, var)) > SUCCESS)
		{
			while (ft_isprint(var->c) && str[var->i] != var->c)
			{
				++var->i;
				if (ft_isin(var->c, &str[var->i + 1]))
					++var->i;
			}
			if (ft_isprint(var->c) && var->c == str[var->i])
				++var->i;
			if (check_deploy(&str[var->i], &match[ft_strpchr(match, CL_SQUAR) + 1], 1, var) > SUCCESS)
			{
				var->j += ft_strpchr(&match[var->j], CL_SQUAR) + 1;
				return (SUCCESS);
			}
			else
			{
				var->i = val;
				++var->i;
				backtracking_deployement(var, match, str, flag);
			}
		}
		else
			return (ERROR);
	}
	else if (flag == 1)
	{
		var->s = 1;
		match_id(var, match, str, flag);
	}
	else if (flag >= 2)
	{
		deployement_limit(var, match, str, flag);
		var->s = 1;
	}
	return (SUCCESS);
}

int
	spread_matching(t_glob *var, char *match, char *str, int flag)
{
	int	len_s;

	len_s = ft_strlen(str);
	if (var->x == 1)
	{
		if (match[var->j] == str[var->i])
			++var->i;
		else
			var->diff += 1;
		++var->j;
		if (!match[var->j] && flag >= 2)
			var->i = len_s;
	}
	if (var->x == 2)
	{
		deployement_limit(var, match, str, flag);
		var->s = 1;
	}
	if (var->x == 3)
	{
		++var->i;
		++var->j;
		if (!match[var->j] && flag >= 2)
			var->i = len_s;
	}
	if (var->x == 4)
	{
		while (match[var->j] && match[var->j] == STAR)
			++var->j;
		if (match[var->j] == OP_SQUAR)
			backtracking_deployement(var, match, str, flag);
		else if (ft_isalnum(match[var->j]))
		{
			while (str[var->i] && str[var->i] != match[var->j])
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
				while (match[var->j] != str[var->i])
					--var->i;
				var->s = 0;
			}
			if (match[var->j] == str[var->i])
				++var->i;
			else
				var->diff += 1;
			++var->j;
		}
		else if (!match[var->j] && match[var->j - 1] == STAR && flag >= 2)
			var->i = len_s;
	}
	var->n = var->i;
	return (SUCCESS);
}

static int	check_pattern(t_glob *var, char *match)
{
	if (var->j == 0 && ft_isalnum(match[var->j]))
		var->x = 1;
	else if (match[var->j] == OP_SQUAR && match[ft_strpchr(&match[var->j], CL_SQUAR) + 1] == STAR)
	{
		var->x = 2;
		var->s = 1;
	}
	else if (match[var->j] == WHY)
	{
		var->w = 1;
		var->x = 3;
	}
	else if (match[var->j] == STAR)
		var->x = 4;
	return (SUCCESS);
}

int
	complex_pattern_matching(t_glob *var, char *match, char *str, int flag)
{
	int	len_m;

	len_m = ft_strlen(match);
	while (var->j < len_m && match[var->j])
	{
		check_pattern(var, match);
		if (var->x)
		{
			spread_matching(var, match, str, flag);
			var->x = 0;
		}
		else
		{
			match_id(var, match, str, flag);
			var->n = var->i;
		}
	}
	var->n = var->i;
	return (SUCCESS);
}

char	*pattern_matching(char *str, char *match, int flag)
{
	t_glob	var;

	init_glob_vars(&var);
	if (!ft_isin(STAR, match))
		simple_pattern_matching(&var, match, str, flag);
	else
		complex_pattern_matching(&var, match, str, flag);
/*	ft_printf("here %s\n", str);
	ft_printf("diff %d\n", var.diff);
	ft_printf("i %d\n", var.i);
	ft_printf("srtr %d\n", ft_strlen(str));
	ft_printf("--------------------------------------------------------\n");*/
	if (flag == 2 && !var.diff)
		return (&str[var.i]);
	else if (flag == 1 && !var.diff)
		return ((var.n != 0) ? &str[var.n] : str);
	else if (flag == 3)
		return ((((int)ft_strlen(str) != var.i) || var.diff) ? EMPTY_STR : str);
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
