/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_free_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:02:09 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/31 16:02:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_btree.h"

void    *btree_free_node(struct s_btree *node, void (*del)(void *))
{
    void    *data;

    data = NULL;
    if (node)
    {
        if (del)
            del(node->data);
        else
            data = node->data;
        free(node);
    }
    return (data);
}