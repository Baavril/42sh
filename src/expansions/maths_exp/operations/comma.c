/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comma.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:24:45 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/12 14:31:23 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_expansion.h"

int				ft_comma(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = right;
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
