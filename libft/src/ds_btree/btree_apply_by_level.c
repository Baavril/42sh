/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:04:14 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/22 13:04:28 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_queue.h"
#include "ft_btree.h"

static __inline__ void	apply_at_level(struct s_queue *queue,
	void (*applyf)(void *item, size_t current_level, size_t is_first_elem),
	size_t level, size_t nb_node_at_level)
{
	struct s_btree *node;
	_Bool		isfirst;

	isfirst = 1;
	while (nb_node_at_level)
	{
		node = queue_dequeue(queue, NULL);
		applyf(node->data, level, isfirst);
		if (node->left)
			queue_enqueue(queue, node->left);
		if (node->right)
			queue_enqueue(queue, node->right);
		--nb_node_at_level;
		isfirst &= ~(1 << 0);
	}
}

void	btree_apply_by_level(struct s_btree *root, void (*applyf)(void *item, size_t current_level, size_t is_first_elem))
{
	struct s_queue	queue;
	size_t		level;
	size_t		nb_node_at_level;

	queue = (struct s_queue){.front = NULL, .rear = NULL};
	if (root)
	{
		level = 0;
		queue_enqueue(&queue, (void*)root);
		while (!queue_isempty(&queue))
		{
			nb_node_at_level = queue_size(&queue);
			apply_at_level(&queue, applyf, level, nb_node_at_level);
			++level;
		}
	}
}
