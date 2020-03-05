/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_apply_to_each.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:07:16 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:33:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

void	stack_apply_to_each(struct s_stack **top, void (*f)())
{
	struct s_stack	*element;

	element = *top;
	while (element)
	{
		f(element->data);
		element = element->previous;
	}
}
