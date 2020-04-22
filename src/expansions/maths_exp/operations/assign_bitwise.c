/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_bitwise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:47:52 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/13 20:54:14 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_variables.h"
#include "maths_expansion.h"

int		ft_r_shift_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left >> right;
		setshvar(var_name, left >> right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_l_shift_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
			&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left << right;
		setshvar(var_name, left << right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_bitwiseand_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
			&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left & right;
		setshvar(var_name, left & right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_bitwiseor_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
			&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left | right;
		setshvar(var_name, left | right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int		ft_bitwisexor_assign(void *left_cmd, void *right_cmd, int64_t *res)
{
	char		*var_name;
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
			&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		var_name = ((t_maths_ast*)left_cmd)->tokens->content->token;
		*res = left ^ right;
		setshvar(var_name, left ^ right);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
