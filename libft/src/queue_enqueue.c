/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_enqueue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:50:06 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 08:52:58 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

void	queue_enqueue(struct s_queue *queue, void *data)
{
	struct s_qnode	*node;

	node = queue_create_node(data);
	if (node)
	{
		if (queue->rear)
			(queue->rear)->previous = node;
		queue->rear = node;
		if (!queue->front)
			queue->front = queue->rear;
	}
}
