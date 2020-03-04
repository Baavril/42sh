/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:54:44 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/03 18:24:48 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_expansion.h"

int				ft_logic_neg(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, NO_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = (right) ? 0 : 1;
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int				ft_logic_and(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if ((left))
		{
			if (ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
			{
				*res = (right);
				return (CONV_SUCCESS);
			}
			return (CONV_FAIL);
		}
		*res = 0;
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int				ft_logic_or(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if (!(left))
		{
			if (ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
			{
				*res = (right);
				return (CONV_SUCCESS);
			}
			return (CONV_FAIL);
		}
		*res = 1;
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
