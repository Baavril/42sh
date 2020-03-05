/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_reverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 08:54:04 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_queue.h"

void	queue_reverse(struct s_queue *queue)
{
	struct s_qnode	*node;
	struct s_qnode	*prev;
	struct s_qnode	*tmp;

	prev = NULL;
	node = queue->front;
	while (node)
	{
		tmp = node->previous;
		node->previous = prev;
		prev = node;
		node = tmp;
	}
	if (queue->front)
	{
		tmp = queue->front;
		queue->front = queue->rear;
		queue->rear = tmp;
	}
}
