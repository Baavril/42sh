/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:25:20 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:35:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

struct s_stack	*stack_initialize(void *data)
{
	struct s_stack	*element;

	element = stack_create_element(data);
	if (element)
	{
		element->previous = NULL;
		return (element);
	}
	return (NULL);
}
