/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:00:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:48:51 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_btree.h"

static inline size_t	ft_max(size_t a, size_t b)
{
	return (a > b ? a : b);
}

size_t					btree_level_count(struct s_btree *root)
{
	if (!root)
		return (0);
	return (ft_max(1 + btree_level_count(root->left),
				1 + btree_level_count(root->right)));
}
