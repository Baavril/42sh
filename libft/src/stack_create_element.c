/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_create_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:22:33 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:34:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "ft_stack.h"

struct s_stack	*stack_create_element(void *data)
{
	struct s_stack	*element;

	element = (struct s_stack*)ft_memalloc(sizeof(struct s_stack));
	if (element)
		element->data = data;
	return (element);
}
