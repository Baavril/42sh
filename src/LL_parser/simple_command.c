/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:36:39 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/14 14:11:52 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "libft.h"

/*
 * cmd_suffix       : io_redirect      cmd_suffix
 *                  | io_redirect
 *                  | WORD             cmd_suffix
 *                  | WORD
 *     node            tmp1               tmp2
 */
t_node	*cmd_suffix(t_token tok)
{
	t_node	*node;
	t_elem	tmp1;

	if (((tmp1.v = io_redirect(tok))) || (tmp1.c = word(tok))) //ALED
	{
		node = malloc(sizeof(t_node));
		node->left = tmp1;
		node->right.v = NULL;
		if (is_potential(peek(), N_SUFFIX))
			node->right.v = cmd_suffix(gnt(NULL));
		node->f	= i_suffix;
		return(node);
	}
	return(NULL);
}

/*
 * exec             : cmd_word         cmd_suffix
 *                  | cmd_word
 *     node            tmp1               tmp2
 */
t_node *exec(t_token tok)
{
	t_node	*node;
	char	*tmp1;

	if ((tmp1 = cmd_word(tok)))
	{
		node = malloc(sizeof(t_node));
		node->left.c = tmp1;
		node->right.v = NULL;
		if (is_potential(peek(), N_SUFFIX))
			node->right.v = cmd_suffix(gnt(NULL));
		node->f	= i_exec;
		return(node);
	}
	return(NULL);
}

/*
 * cmd_prefix       : io_redirect      cmd_prefix
 *                  | io_redirect
 *                  | ASSIGNEMENT_WORD cmd_prefix
 *                  | ASSIGNMENT_WORD
 *     node            tmp1               tmp2
 */
t_node	*cmd_prefix(t_token tok)
{
	t_node	*node;
	t_elem	tmp1;

	if (((tmp1.v = io_redirect(tok))) || (tmp1.c = assig_word(tok))) //ALED
	{
		node = malloc(sizeof(t_node));
		node->left = tmp1;
		node->right.v = NULL;
		if (is_potential(peek(), N_PREFIX))
			node->right.v = cmd_prefix(gnt(NULL));
		node->f	= i_prefix;
		return(node);
	}
	return(NULL);
}

/*
 * simple_command   : cmd_prefix       exec
 *                  | NULL             exec
 *                  | cmd_prefix
 *     node            tmp1            tmp2
 */
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
			node->f = i_simple_command;
			return(node);
		}
		return(tmp1);
	}
	else if (is_potential(tok, N_CMD_NAME))
	{
		node = malloc(sizeof(t_node));
		node->left.v = NULL;
		node->right.v = exec(tok);
		node->f = i_simple_command;
		return(node);
	}
	return(NULL);
}

/*
 * command         : simple_command
 */
t_node	*command(t_token tok)
{
	return(simple_command(tok));
}
