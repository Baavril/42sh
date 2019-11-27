/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:36:39 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/27 15:34:26 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "libft.h"

t_node	*cmd_suffix(t_token tok)
{
	t_node	*node;
	t_elem	tmp1;

	if (((tmp1.v = io_redirect(tok))) || (tmp1.c = word(tok)))
	{
		node = malloc(sizeof(t_node));
		node->left = tmp1;
		if (is_potential(peek(), N_SUFFIX))
			node->right.v = cmd_suffix(gnt(NULL));
		node->f	= NULL; //should be i_suffix();
		return(node);
	}
	return(NULL);
}

t_node *exec(t_token tok)
{
	t_node	*node;
	char	*tmp1;

	if ((tmp1 = cmd_word(tok)))
	{
		node = malloc(sizeof(t_node));
		node->left.c = tmp1;
		if (is_potential(peek(), N_SUFFIX))
			node->right.v = cmd_suffix(gnt(NULL));
		node->f	= NULL; //should be i_exec();
		return(node);
	}
	return(NULL);
}

t_node	*cmd_prefix(t_token tok)
{
	t_node	*node;
	t_elem	tmp1;

	if (((tmp1.v = io_redirect(tok))) || (tmp1.c = assig_word(tok))) //HELP
	{
			node = malloc(sizeof(t_node));
			node->left = tmp1;
		if (is_potential(peek(), N_PREFIX))
			node->right.v = cmd_prefix(gnt(NULL));
		node->f	= NULL; //should be i_prefix();
		return(node);
	}
	return(NULL);
}

t_node	*simple_command(t_token tok)
{
	t_node *node;
	t_node *tmp1;

	if ((tmp1 = cmd_prefix(tok)))
	{
		if (is_potential(peek(), N_CMD_WORD))
		{
			node = malloc(sizeof(t_node));
			node->left.v = tmp1;
			node->right.v = exec(gnt(NULL));
			node->f = NULL; //should be i_simple_command();
			return(node);
		}
		return(tmp1);
	}
	else if (is_potential(tok, N_CMD_NAME))
	{
		return(exec(tok));
	}
	return(NULL);
}

t_node	*command(t_token tok)
{
	return(simple_command(tok));
}
