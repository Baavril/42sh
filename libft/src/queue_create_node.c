/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:44:01 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 08:51:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "ft_queue.h"

struct s_qnode	*queue_create_node(void *data)
{
	struct s_qnode	*node;

	node = (struct s_qnode*)ft_memalloc(sizeof(struct s_qnode));
	if (node)
		node->data = data;
	return (node);
}
