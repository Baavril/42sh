/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 08:40:59 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/05 10:07:30 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int				shape(t_node *node)
{
	if (node->f == i_less
	||  node->f == i_dless
	||  node->f == i_lessand
	||  node->f == i_great
	||  node->f == i_dgreat
	||  node->f == i_greatand
	||  node->f == i_lessgreat
	||  node->f == i_dlessdash
	||  node->f == i_clobber)
		return(0b11);
	if (node->f == i_prefix
	||  node->f == i_suffix_word
	||  node->f == i_suffix_redirect
	||  node->f == i_builtin
	||  node->f == i_exec)
		return(0b10);
	else
		return(0b00);
}

int				free_ast(t_node *node)
{
	int node_type;

	node_type = shape(node);
	ft_printf("new node with shape %d%d\n", (node_type & 0b10) / 2, node_type & 0b01);
	if (node->left.c || node->left.v)
	{
		if (node_type & 0b10)
		{
			ft_printf("free %s!\n", node->left.c);
			free(node->left.c);
		}
		else
			free_ast(node->left.v);
		node->left.c = NULL;
	}
	if (node->right.c || node->right.v)
	{
		if (node_type & 0b01)
		{
			ft_printf("free %s!\n", node->right.c);
			free(node->right.c);
		}
		else
			free_ast(node->right.v);
		node->right.c = NULL;
	}
	free(node);
	return (0);
}
