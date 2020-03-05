/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:55:25 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 09:34:33 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

void	stack_delete(struct s_stack **top, void (*del_data)(void *))
{
	while (*top)
		stack_pop(top, del_data);
}
