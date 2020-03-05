/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_apply_to_each.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:40:18 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 08:50:50 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

void	queue_apply_to_each(struct s_queue *queue, void (*f)())
{
	struct s_qnode	*node;

	node = queue->front;
	while (node)
	{
		f(node->data);
		node = node->previous;
	}
}
