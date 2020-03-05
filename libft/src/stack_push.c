/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:19:37 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:37:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

void	stack_push(struct s_stack **top, void *data)
{
	struct s_stack	*push;

	if (*top)
	{
		push = stack_create_element(data);
		if (push)
		{
			push->previous = *top;
			*top = push;
		}
	}
	else
		*top = stack_initialize(data);
}
