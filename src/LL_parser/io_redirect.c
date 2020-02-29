/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:33:42 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 15:36:12 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "libft.h"
#include <unistd.h>

extern int g_parsingerr;

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
	&i_andgreat,
};

t_node	*io_redirect(t_token tok)
{
	t_node		*node;
	char		*tmp1;
	extern int	g_alias_treated;
	int			bckp;

	if ((tmp1 = io_number(tok)))
		tok = gnt(NULL, 0);
	if (tok.type >= LESS && tok.type <= ANDGREAT)
	{
		node = malloc(sizeof(t_node));
		node->left.c = tmp1;
		node->f = g_redirect[tok.type - LESS];
		bckp = g_alias_treated;
		g_alias_treated = 1;
		if (tok.type == DLESS
		|| tok.type == DLESSDASH)
			node->right.c = here_end(gnt(NULL, 0));
		else
			node->right.c = filename(gnt(NULL, 0));
		g_alias_treated = bckp;
		if (!node->right.c && (g_parsingerr = 1))
			ft_dprintf(STDERR_FILENO, "parsing error near redirection\n");
		return (node);
	}
	return (NULL);
}
