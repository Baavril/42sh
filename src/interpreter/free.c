/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 08:40:59 by bprunevi          #+#    #+#             */
/*   Updated: 2020/07/09 01:16:34 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <unistd.h>

int				astdel(t_node *node)
{
	int node_type;

	if (!node)
		return (1);
	node_type = shape(node);
	if (node->left.c || node->left.v)
	{
		if (node_type & 0b10)
			free(node->left.c);
		else
			astdel(node->left.v);
		node->left.c = NULL;
	}
	if (node->right.c || node->right.v)
	{
		if (node_type & 0b01)
			free(node->right.c);
		else
			astdel(node->right.v);
		node->right.c = NULL;
	}
	free(node);
	return (0);
}
