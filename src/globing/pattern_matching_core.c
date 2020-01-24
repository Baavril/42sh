/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_core.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/24 15:32:40 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

int		fixing_star_flag(t_glob *var, char *match, char *str, int flag)
{
	//	ft_printf("here12 %s\n", &match[var->j]);
	//	ft_printf("here23 %s\n", &str[var->i]);
	while ((size_t)var->j < ft_strlen(match) && match[var->j] && match[var->j] == STAR && match[var->j + 1] != '\0')
	{
		if (match[var->j + 1] != STAR)
		{
			if (match[var->j + 1] != OP_SQUAR)
			{
				star_no_deployement(var, match, str, flag);
			}
			else
			{
				star_deployement(var, match, str, flag);
			}
			var->n = var->i + 1;
			//ft_printf("n2 = %d\n", var->n);
			if (match[var->j + 1] == STAR && match[var->j + 2] == OP_SQUAR)
				++var->i;
		}
		++var->j;
	}
	return (SUCCESS);
}

int		reach_next_star_flag(t_glob *var, char *match, char *str, int flag)
{
	while ((size_t)var->j < ft_strlen(match) && match[var->j] && match[var->j] != STAR)
	{
		if ((size_t)var->i < ft_strlen(str) && str[var->i + 1] == match[var->j] && match[var->j - 1] == STAR && match[var->j + 1] != str[var->i + 1] && match[var->j + 1] != STAR)
			++var->i;
//		ft_printf("here2 %s\n", &match[var->j]);
//		ft_printf("here3 %s\n", &str[var->i]);
		if (var->i <= (int)ft_strlen(str) && match[var->j] != str[var->i])
		{
			if (match[var->j] == WHY && str[var->i] && ft_isprint(str[var->i]))
				var->diff -= 1;
			if (match[var->j] == OP_SQUAR)
			{
				if ((ft_strpchr(&match[var->j], CL_SQUAR)) > 0
				&& check_deploy(&str[var->i], &match[var->j], flag, 0)
				>= SUCCESS)
				{
				//	ft_printf("diff18 = %c\n", match[var->j]);
					var->j += ft_strpchr(&match[var->j], CL_SQUAR);
					//var->x += ft_strpchr(&match[var->i + var->x], CL_SQUAR) - 1;
					var->diff -= 1;
				//	ft_printf("diff18 = %c\n", match[var->j]);
				}
			}
			var->diff += 1;
//			ft_printf("diff19 = %d\n", var->diff);
		}
		++var->i;
		if (match[var->j] != STAR)
			++var->j;
		var->n = var->i;
	}
	//	ft_printf("here4 %s\n", &match[var->j]);
	//	ft_printf("here5 %s\n", &str[var->i]);
	//ft_printf("i1 %d\n", var->i);
	return (SUCCESS);
}

int		positionning_star_flag(t_glob *var, char *str, char *match)
{
	while (var->i <= (int)ft_strlen(str) && str[var->i]
	&& match[var->j] && match[var->j] == STAR
	&& match[var->j + 1] == '\0' && !var->diff)
		++var->i;
//	if ((var->i + var->x + 1) <= (int)ft_strlen(match)
//	&& match[var->i + var->x + 1] == STAR)
//		++var->x;
	//	ft_printf("here4 %s\n", &match[var->j]);
	//	ft_printf("here5 %s\n", &str[var->i]);
	return (SUCCESS);
}
