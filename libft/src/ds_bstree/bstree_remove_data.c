/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_remove_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:50:38 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 13:50:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_btree.h"

static __inline__ struct s_btree	*two_children_case(struct s_btree *root, void (*del)(void *)) 
{
	struct s_btree	*parent; 
	struct s_btree	*successor; 

	parent = root->right; 
	successor = root->right; 
	while (successor->left)
	{ 
		parent = successor; 
		successor = successor->left; 
	} 
	parent->left = successor->right;
	del(root->data);	
	root->data = successor->data;	
	del(successor);
	return (root); 

}

static __inline__ struct s_btree	*delete_node(struct s_btree *root, void (*del)(void *)) 
{
	struct s_btree	*node; 

	if (!(root->left))
	{ 
		node = root->right; 
		del(root->data);
		free(root);
		return (node); 
	} 
	else if (!(root->right))
	{ 
		node = root->left; 
		del(root->data);
		free(root);
		return (node); 
	} 
	else
		return (two_children_case(root, del));
}

static struct s_btree	*find_node(struct s_btree *root, void *data_ref, int (*cmpf)(void*, void*), void (*del)(void *)) 
{ 
	if (!root) 
		return (root); 
	if (cmpf(root->data, data_ref) > 0)
	{ 
		root->left = find_node(root->left, data_ref, cmpf, del); 
		return (root); 
	} 
	else if (cmpf(root->data, data_ref) < 0)
	{ 
		root->right = find_node(root->right, data_ref, cmpf, del); 
		return (root); 
	}
	return (delete_node(root, del));	
} 

void    bstree_remove_data(struct s_btree **root, void *data_ref, int (*cmpf)(void *, void *), void (*del)(void *))
{
	if (*root)
		*root = find_node(*root, data_ref, cmpf, del);
}
