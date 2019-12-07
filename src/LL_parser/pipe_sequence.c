/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:48:12 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/03 12:35:53 by bprunevi         ###   ########.fr       */
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

	if ((tmp1 = command(tok)))
	{
		if (is_potential(peek(), N_PIPE))
		{
			gnt(NULL);
			if (!(tmp2 = pipe_sequence(gnt(NULL))))
				exit(ft_printf("error in pipe_sequence\n"));
			node = malloc(sizeof(t_node));
			node->left.v = tmp1;
			node->right.v = tmp2;
			ft_printf("pipeseq with 2 elems was created\n");
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
	return(pipeline(tok));
}

