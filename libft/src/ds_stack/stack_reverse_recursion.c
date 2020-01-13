/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_reverse_recursion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:22:36 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:37:55 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

static void	insert_element(struct s_stack **top, void *data)
{
	void	*restrict element_data;

	if (stack_isempty(top))
		stack_push(top, data);
	else
	{
		element_data = stack_pop_get_data(top);
		insert_element(top, data);
		stack_push(top, element_data);
	}
}

void		stack_reverse_recursion(struct s_stack **top)
{
	void	*restrict element_data;

	element_data = stack_pop_get_data(top);
	if (element_data)
	{
		stack_reverse_recursion(top);
		insert_element(top, element_data);
	}
}
