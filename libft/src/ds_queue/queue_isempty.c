/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_isempty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:56:16 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 08:53:33 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

_Bool	queue_isempty(const struct s_queue *queue)
{
	if (!queue->rear && !queue->front)
		return (1);
	return (0);
}
