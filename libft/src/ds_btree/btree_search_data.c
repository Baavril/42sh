/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:50:25 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/22 12:50:44 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_btree.h"

struct s_btree	*btree_search_data(struct s_btree *root, void *data_ref, int (*cmpf)(void *, void *))
{
	void	*node;

	if (!root)
		return (NULL);
	if ((node = btree_search_data(root->left, data_ref, cmpf)))
		return (node);
	if (!(cmpf(data_ref, root->data)))
		return (root);
	return (btree_search_data(root->right, data_ref, cmpf));
}
