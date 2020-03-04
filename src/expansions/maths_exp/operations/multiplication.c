/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:47:32 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/15 15:35:25 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_expansion.h"
#include "error.h"

extern char		*g_exptok;

int				ft_mul(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left * right;
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int				ft_exp(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if (right < 0)
		{
			psherror(e_neg_exp, g_exptok, e_maths_type);
			return (CONV_FAIL);
		}
		if (left == 0)
			*res = 0;
		else if (right == 0)
			*res = 1;
		else
			*res = ft_pow(left, right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int				ft_div(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if (right != 0)
		{
			*res = left / right;
			return (CONV_SUCCESS);
		}
		psherror(e_division_zero, g_exptok, e_maths_type);
	}
	return (CONV_FAIL);
}

int				ft_mod(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if (right != 0)
		{
			*res = left / right;
			return (CONV_SUCCESS);
		}
		psherror(e_division_zero, g_exptok, e_maths_type);
	}
	return (CONV_FAIL);
}
