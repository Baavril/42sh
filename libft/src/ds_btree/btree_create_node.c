/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:40:22 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/21 17:40:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_btree.h"

struct s_btree	*btree_create_node(void *data)
{
	struct s_btree	*node;

	node = (struct s_btree*)malloc(sizeof(struct s_btree));
	if (node)
	{
		node->left = NULL;
		node->right = NULL;
		node->data = data;
		return (node);
	}
	else
	{
		return (NULL);
	}
}
