/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:33:42 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/03 19:07:46 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "libft.h"

/*
 * io_redirect		: IO_NUMBER filename  DEPENDS
 * 					| IO_NUMBER end_here  DEPENDS
 *  node                left      right    f()
 */
t_node	*io_redirect(t_token tok)
{
	t_node	*node;
	char	*tmp1;

	if ((tmp1 = io_number(tok)))
			tok = gnt(NULL);
	if (   tok.type == LESS
		|| tok.type == LESSAND
		|| tok.type == GREAT
		|| tok.type == GREATAND
		|| tok.type == DGREAT
		|| tok.type == LESSGREAT
		|| tok.type == CLOBBER
		|| tok.type == DLESS
		|| tok.type == DLESSDASH)
	{
		node = malloc(sizeof(t_node));
		node->left.c = tmp1;
		node->f = i_debugredirect;
		if (   tok.type == LESS
			|| tok.type == LESSAND
			|| tok.type == GREAT
			|| tok.type == GREATAND
			|| tok.type == DGREAT
			|| tok.type == LESSGREAT
			|| tok.type == CLOBBER)
			node->right.c = filename(gnt(NULL));
		else if (  tok.type == DLESS
				|| tok.type == DLESSDASH)
			node->right.c = here_end(gnt(NULL));
		if (!node->right.c)
			exit(ft_printf("parsing error in io_redirect"));
		return(node);
	}
	return (NULL);
}
