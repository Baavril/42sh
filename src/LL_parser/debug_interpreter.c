/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_interpreter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:44:12 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/14 16:05:25 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "jcont.h"

/*
 * comp_list	: and_or SEMI comp_list
 */
t_node	*comp_list(t_token tok)
{
	t_node	*node;
	t_node	*tmp1;
	t_node	*tmp2;

	if ((tmp1 = and_or(tok)))
	{
		if (is_potential(peek(), N_SEMI))
		{
			gnt(NULL);
			if ((tmp2 = comp_list(gnt(NULL))))
			{
				node = malloc(sizeof(t_node));
				node->left.v = tmp1;
				node->right.v = tmp2;
				node->f = i_comp_list;
				return(node);
			}
		}
		if (is_potential(peek(), N_AND))
		{
			gnt(NULL);
			if ((tmp2 = comp_list(gnt(NULL))))
			{
				node = malloc(sizeof(t_node));
				node->left.v = tmp1;
				node->right.v = tmp2;
				node->f = i_and_list;
				return(node);
			}
		}
		return(tmp1);
	}
	return(NULL);
}

void	interpret(t_node *node)
{
	if (node)
	{
		node->f(node->left, node->right);
		ft_launch_job("plop", FOREGROUND);
		astdel(node);
		node = NULL;
	}
}

void	debug_parser(char *input)
{
	interpret(comp_list(get_next_token(input)));
	gnt(NULL);
}
