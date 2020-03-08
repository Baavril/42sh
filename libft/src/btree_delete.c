/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:50:38 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 13:50:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_btree.h"

static void	btree_postfix_deletion(struct s_btree *root)
{
	if (root->left)
		btree_postfix_deletion(root->left);
	if (root->right)
		btree_postfix_deletion(root->right);
	free(root);
}

void		btree_delete(struct s_btree **root, void (*del)(void *))
{
	btree_apply_prefix(*root, del);
	btree_postfix_deletion(*root);
	*root = NULL;
}
