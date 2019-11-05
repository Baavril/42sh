/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:27:51 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:40:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

void	stack_swap(struct s_stack **top)
{
	struct s_stack	*tmp;

	if (!*top)
		return ;
	else if (!(*top)->previous)
		return ;
	tmp = *top;
	*top = (*top)->previous;
	tmp->previous = (*top)->previous;
	(*top)->previous = tmp;
}
