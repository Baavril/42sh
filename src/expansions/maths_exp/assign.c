/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 18:12:11 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/05 11:29:51 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"

int		ft_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_r_shift_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left >> right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left >> right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_l_shift_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left << right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left << right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
int		ft_add_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left + right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left + right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_sub_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left - right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left - right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_mul_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left * right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left * right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_div_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if (!right)
			return (CONV_FAIL); //div par zero
		*res = left / right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left / right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_mod_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		if (!right)
			return (CONV_FAIL); //div par zero
		*res = left % right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left % right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_bitwiseand_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left & right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left & right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_bitwiseor_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left | right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left | right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int				ft_bitwisexor_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left ^ right;
		setshvar(((t_maths_ast*)left_cmd)->tokens->content->token, left ^ right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
