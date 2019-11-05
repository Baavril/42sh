/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:22:36 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:40:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

static void	insert_sorted_element(struct s_stack **top, void *data, int (*cmp)())
{
	void	*__restrict__ element_data;

	if (stack_isempty(top) || cmp((*top)->data, data) > 0)
		stack_push(top, data);
	else
	{
		element_data = stack_pop_get_data(top);
		insert_sorted_element(top, data, cmp);
		stack_push(top, element_data);
	}
}

void		stack_sort(struct s_stack **top, int (*cmp)())
{
	void	*__restrict__ element_data;

	element_data = stack_pop_get_data(top);
	if (element_data)
	{
		stack_sort(top, cmp);
		insert_sorted_element(top, element_data, cmp);
	}
}
