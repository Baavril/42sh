/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_postfix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:40:22 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:50:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_btree.h"

void		btree_apply_postfix(struct s_btree *root, void (*applyf)(void *))
{
	if (root->left)
		btree_apply_postfix(root->left, applyf);
	if (root->right)
		btree_apply_postfix(root->right, applyf);
	applyf(root->data);
}
