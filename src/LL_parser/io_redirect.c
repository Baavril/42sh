/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:33:42 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/28 10:12:19 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "libft.h"

t_node	*io_file(t_token tok)
{
	t_node	*node;

	if (   tok.type == LESS
		|| tok.type == LESSAND
		|| tok.type == GREAT
		|| tok.type == GREATAND
		|| tok.type == DGREAT
		|| tok.type == LESSGREAT
		|| tok.type == CLOBBER)
	{
		ft_printf("tok_type %d detected ! \n", tok.type); //
		node = malloc(sizeof(t_node));
		node->left.v = NULL; // should be tok.type -------------------------------------------
		tok = gnt(NULL);
		if ((node->right.c = filename(tok)))
		{
			node->f = NULL; // should be one in an array of i_f() 
			return(node);
		}
		else
			exit(ft_printf("parsing error in io_file")); 
			//WARNING : 
			//exit() calls like these are a temporary solution only
			//since they do not free any malloc() or quit properly.
	}
	return(NULL);
}

t_node	*io_here(t_token tok)
{
	t_node	*node;

	if (  (tok.type == DLESS)
		| (tok.type == DLESSDASH))
	{
		ft_printf("tok_type %d detected ! \n", tok.type);
		node = malloc(sizeof(t_node));
		node->left.v = NULL; // should be tok.type -------------------------------------------------------------------
		tok = gnt(NULL);
		if ((node->right.c = here_end(tok)))
		{
			node->f = NULL; // SHOULD BE one in an array of i_f() 
			return(node);
		}
		else
			exit(ft_printf("parsing error in io_here")); //
	}
	return(NULL);
}

t_node	*io_redirect(t_token tok)
{
	t_node	*node;
	char	*tmp1;
	t_node	*tmp2;

	if ((tmp2 = io_file(tok)) || (tmp2 = io_here(tok)))
		return (tmp2);
	else if ((tmp1 = io_number(tok)))
	{
		tok = gnt(NULL);
		if ((tmp2 = io_file(tok)) || (tmp2 = io_here(tok)))
		{
			node = malloc(sizeof(t_node));
			node->left.c = tmp1;
			node->right.v = tmp2;
			node->f = NULL; //should be i_io_redirect ? ptet. ptet pas. a etudier.
			return (node);
		}
		exit(ft_printf("parsing error in io_redirect")); //
	}
	return (NULL);
}
