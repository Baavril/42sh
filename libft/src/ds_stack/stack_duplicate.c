/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:28:33 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:34:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

void	stack_duplicate(struct s_stack **top, void *(*copy_data)())
{
	void	*data_copy;

	data_copy = NULL;
	if (*top)
	{
		data_copy = copy_data((*top)->data);
		if (data_copy)
			stack_push(top, data_copy);
	}
}
