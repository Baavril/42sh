/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_reverse_recursion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:45:55 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 08:54:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "ft_queue.h"

void	queue_reverse_recursion(struct s_queue *queue)
{
	void	*data;

	if (!queue_isempty(queue))
	{
		data = queue_dequeue(queue, NULL);
		queue_reverse_recursion(queue);
		queue_enqueue(queue, data);
	}
}
