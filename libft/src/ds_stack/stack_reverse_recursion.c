/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_reverse_recursion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:22:36 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:39:20 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

static void	insert_element(struct s_stack **top, void *data)
{
	void	*__restrict__ element_data;

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
	void	*__restrict__ element_data;

	element_data = stack_pop_get_data(top);
	if (element_data)
	{
		stack_reverse_recursion(top);
		insert_element(top, element_data);
	}
}
