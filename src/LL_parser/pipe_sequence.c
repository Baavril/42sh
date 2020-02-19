/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:48:12 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/19 16:22:31 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "libft.h"

/*
 * pipe_sequence    : command
 *                  | command PIPE pipe_sequence
 *     node            tmp1          tmp2
 */
static t_node	*pipe_sequence(t_token tok)
{
	t_node *node;
	t_node *tmp1;
	t_node *tmp2;
	extern int			g_alias_treated;

	if ((tmp1 = command(tok)))
	{
		if (is_potential(peek(), N_PIPE))
		{
			g_alias_treated = 0;
			eat();
			if (!(tmp2 = pipe_sequence(eat())))
				exit(ft_printf("error in pipe_sequence\n"));
			node = malloc(sizeof(t_node));
			node->left.v = tmp1;
			node->right.v = tmp2;
			node->f = i_pipe_sequence;
			return(node);
		}
		return(tmp1);
	}
	return(NULL);
}

/*
 * pipeline         : pipe_sequence
 */
static t_node	*pipeline(t_token tok)
{
	return(pipe_sequence(tok));
}

/*
 * and_or           : pipeline
 */
t_node	*and_or(t_token tok)
{
	t_node *node;
	t_node *tmp1;
	t_node *tmp2;
	int (*f)(t_elem left, t_elem right);

	if ((tmp1 = pipeline(tok)))
	{
		if ((is_potential(peek(), N_AND_IF) && (f = i_and_op))
		 || (is_potential(peek(), N_OR_IF) && (f = i_or_op)))
		{
			eat();
			if (!(tmp2 = and_or(eat())))
				exit(ft_printf("error in and_or\n"));
			node = malloc(sizeof(t_node));
			node->left.v = tmp1;
			node->right.v = tmp2;
			node->f = f;
			return(node);
		}
		return(tmp1);
	}
	return(NULL);
}

/*
 * comp_list	: and_or SEMI comp_list
 				| and_or SEMI (null) 
 				| and_or AND  comp_list
 				| and_or AND (null) 
 */
t_node	*comp_list(t_token tok)
{
	t_node	*node;
	t_node	*tmp1;

	if ((tmp1 = and_or(tok)))
	{
		node = malloc(sizeof(t_node));
		node->left.v = tmp1;
		node->f = i_comp_list;
		if (is_potential(peek(), N_SEMI))
			eat();
		if (is_potential(peek(), N_AND))
		{
			eat();
			node->f = i_and_list;
		}
		node->right.v = comp_list(eat());
		return(node);
	}
	return(NULL);
}
