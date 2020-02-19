/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:29:21 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/19 13:40:39 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "jcont.h"

static void	interpret(t_node *node)
{
	if (node)
	{
		node->f(node->left, node->right);
		astdel(node);
		node = NULL;
	}
}

void	execute(char *input)
{
	t_node *AST;
	AST = comp_list(gnt(input, 0));
	eat();
	interpret(AST);
}

