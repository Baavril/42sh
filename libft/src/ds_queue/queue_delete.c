/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:22:27 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/29 13:01:21 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_queue.h"

void	queue_delete(struct s_queue *queue, void (*del)())
{
	while (queue->front)
		queue_dequeue(queue, del);
	queue->rear = NULL;
}
