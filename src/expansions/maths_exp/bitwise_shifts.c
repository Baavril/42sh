/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_shifts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:08:01 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/12 13:36:03 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"

int				ft_l_shift(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left << right;
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int				ft_r_shift(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = left >> right;
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
