/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_dequeue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:50:06 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 08:52:35 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_queue.h"

void	*queue_dequeue(struct s_queue *queue, void (*del)(void *))
{
	struct s_qnode	*node;
	void		*data;

	data = NULL;
	if (queue->front)
	{
		node = queue->front;
		data = queue->front->data;
		queue->front = queue->front->previous;
		if (!queue->front)
			queue->rear = NULL;
		if (del)
			del(data);
		else
			data = node->data;
		free(node);
	}
	return (data);
}
