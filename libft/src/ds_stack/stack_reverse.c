/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_reverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:56:15 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:38:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

void	stack_reverse(struct s_stack **top)
{
	struct s_stack	*tmp;
	struct s_stack	*real_prev;

	if (*top)
	{
		real_prev = *top;
		tmp = (*top)->previous;
		(*top)->previous = NULL;
		*top = tmp;
		while (*top)
		{
			tmp = (*top)->previous;
			(*top)->previous = real_prev;
			real_prev = *top;
			*top = tmp;
		}
		*top = real_prev;
	}
}
