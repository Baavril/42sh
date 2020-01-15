/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:33:42 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/15 12:01:43 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "libft.h"

int		(*g_redirect[])(t_elem left, t_elem right) =
{
	&i_less,
	&i_dless,
	&i_lessand,
	&i_great,
	&i_dgreat,
	&i_greatand,
	&i_lessgreat,
	&i_dlessdash,
	&i_clobber,
};

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
			tok = eat();
	if (   tok.type >= LESS
		&& tok.type <= CLOBBER)
	{
		node = malloc(sizeof(t_node));
		node->left.c = tmp1;
		node->f = g_redirect[tok.type - LESS];
		if (tok.type == DLESS
		 || tok.type == DLESSDASH)
			node->right.c = here_end(eat());
		else
			node->right.c = filename(eat());
		if (!node->right.c)
			exit(ft_printf("parsing error in io_redirect"));
		return(node);
	}
	return (NULL);
}
