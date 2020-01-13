/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:58:02 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/13 20:58:24 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"

int		ft_add_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left + right;
		setshvar(var_name, left + right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_sub_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left - right;
		setshvar(var_name, left - right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_mul_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left * right;
		setshvar(var_name, left * right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_div_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if (!right)
			return (CONV_FAIL); //div par zero
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left / right;
		setshvar(var_name, left / right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_mod_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if (!right)
			return (CONV_FAIL); //div par zero
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left % right;
		setshvar(var_name, left % right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
