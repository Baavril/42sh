/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:48:12 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/27 15:32:38 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "libft.h"

static t_node	*pipe_sequence(t_token tok)
{
	/*POTENTIEL PROBLEME :
	 * pipe_sequence() est right associative selon la grammaire,
	 * mais left associatve selon le code.
	 * Ainsi, il cree un arbre de style 
	 * potentiellement inadapte
	 */
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
			node->left.v = tmp1; //Correspond a command()
			node->right.v = tmp2;// Correspond a pipe_sequence()
			ft_printf("pipeseq with 2 elems was created\n");
			node->f = NULL; //should be i_pipe_sequence();
			return(node);
		}
		return(tmp1);
	}
	return(NULL);
}

static t_node	*pipeline(t_token tok)
{
	return(pipe_sequence(tok)); //TODO
}

t_node	*and_or(t_token tok)
{
	return(pipeline(tok));//bon ca devient ridicule la
}

