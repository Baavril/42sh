/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:23:37 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:36:34 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

void	stack_pop(struct s_stack **top, void (*del_data)(void *))
{
	struct s_stack	*previous;

	if (*top)
	{
		del_data((*top)->data);
		previous = (*top)->previous;
		free(*top);
		*top = previous;
	}
}
