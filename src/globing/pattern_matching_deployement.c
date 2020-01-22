/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_deployement.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/22 10:06:34 by baavril          ###   ########.fr       */
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
		//ft_printf("diff3 = %d\n", var->diff);
	}
	return (SUCCESS);
}

int
	reach_star_flag(t_glob *var, char *match, char *str, int flag)
{
	//ft_printf("here5 %s\n", match);
	//ft_printf("here5 %c\n", match[var->i + var->x]);
	while (match[var->i + var->x] && match[var->i + var->x] != STAR)
	{
		//ft_printf("here7 %s\n", str);
		//ft_printf("i %d\n", var->i);
		//ft_printf("len %d\n", ft_strlen(str));
		//ft_printf("x %d\n", var->x);
		//ft_printf("m %c\n", match[var->x + var->i]);
		if ((size_t)var->i <= ft_strlen(str)
		&& match[var->i + var->x] != str[var->i])
		{
			if (match[var->i + var->x] == WHY
			&& str[var->i] && ft_isprint(str[var->i]))
			{
				var->diff -= 1;
				//ft_printf("diff1 = %d\n", var->diff);
			}
			else if (match[var->i + var->x] == OP_SQUAR)
				deployement_support(var, str, match, flag);
			var->diff += 1;
			//ft_printf("diff2 = %d\n", var->diff);
		}
		++var->i;
	}
	var->j = var->i + var->x;
	var->n = var->i;
	//ft_printf("get_n_value %d\n", var->n);
	return (SUCCESS);
}

int
	star_no_deployement(t_glob *var, char *match, char *str, int flag)
{
	while (var->i <= (int)ft_strlen(str) && str[var->i]
	&& str[var->i] != match[var->j + 1])
	{
		++var->i;
	//ft_printf("i4 %d\n", var->i);
		if (str[var->i] == match[var->j + 1])
		{
			if (flag >= 2 && ft_isin(match[var->j + 1], &str[var->i + 1]))
				++var->i;
		}
		if ((size_t)var->i < ft_strlen(str) && str[var->i] == str[var->i - 1])
			--var->x;
	//ft_printf("i4 %d\n", var->i);
	}
	if (var->i <= (int)ft_strlen(str) && str[var->i] != match[var->j + 1])
	{
		var->diff += 1;
		//ft_printf("diff4 = %d\n", var->diff);
	}
	return (SUCCESS);
}

int
	star_deployement(t_glob *var, char *match, char *str, int flag)
{
	var->c = check_deploy(&str[var->i], &match[var->j + 1], flag, 1);
	//ft_printf("m1 %s\n",&match[var->j]);
	while (ft_isprint(var->c) && str[var->i] != var->c)
		++var->i;
	//ft_printf("see %c\n", var->c);
	//ft_printf("e1 %s\n", &str[var->i]);
//	while ((size_t)var->i < ft_strlen(str) && str[var->i]
//	&& str[var->i] == str[var->i + 1] && (flag >= 2 || match[ft_strlen(match) - 1] == STAR))
//			++var->i;
	if (var->c == ERROR)
	{
		var->diff += 1;
	//	ft_printf("diff5 = %d\n", var->diff);
	}
	var->x += ft_strpchr(&match[var->i + var->x], CL_SQUAR) + 1;
	var->j += ft_strpchr(&match[var->j], CL_SQUAR);
	//ft_printf("m21 %s\n",&match[var->j]);
	if (flag == 1 && (size_t)var->i < ft_strlen(str) && ft_isin(OP_SQUAR, &match[var->j]) && str[var->i] == str[var->i + 1] && match[ft_strlen(match) - 1] == STAR)
		++var->i;
	if (flag >= 2 && !match[var->j + 1])
	{
		++var->i;
		if ((size_t)var->i < ft_strlen(str) && str[var->i] == str[var->i - 1])
			++var->i;
	}
	//ft_printf("e2 %s\n", &str[var->i]);
	return (SUCCESS);
}
