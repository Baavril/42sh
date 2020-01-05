/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:50:32 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/05 11:20:27 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"

int				ft_incr(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, NO_TOKEN) == CONV_SUCCESS)
	{
		*res = left;
		setshvar(((t_maths_ast*)(left_cmd))->tokens->content->token, left + 1);
		return (CONV_SUCCESS);
	}
	if (ft_eval_ast(left_cmd, &left, NO_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = right + 1;
		setshvar(((t_maths_ast*)(right_cmd))->tokens->content->token, right + 1);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int				ft_decr(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, NO_TOKEN) == CONV_SUCCESS)
	{
		*res = left;
		setshvar(((t_maths_ast*)(left_cmd))->tokens->content->token, left - 1);
		return (CONV_SUCCESS);
	}
	if (ft_eval_ast(left_cmd, &left, NO_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = right - 1;
		setshvar(((t_maths_ast*)(right_cmd))->tokens->content->token, right - 1);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
