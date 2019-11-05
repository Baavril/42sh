/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:24:24 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/22 12:25:28 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_btree.h"

void	btree_insert_data(struct s_btree **root, void *data, int (*cmpf)(void *, void *))
{
	struct s_btree	*node;

	node = *root;
	while (node)
	{
		if (cmpf(node->data, data) > 0)
		{
			if (node->left)
				node = node->left;
			else if ((node->left = btree_create_node(data)))
				break ;
		}
		else
		{
			if (node->right)
				node = node->right;
			else if ((node->right = btree_create_node(data)))
				break ;
		}
	}
	if (!*root)
		*root = btree_create_node(data);
}