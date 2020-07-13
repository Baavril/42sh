/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:33:42 by bprunevi          #+#    #+#             */
/*   Updated: 2020/07/13 15:30:22 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "error.h"
#include "parser.h"
#include "curjob.h"
#include "libft.h"
#include <unistd.h>

extern int		g_parsingerr;
extern t_flist	g_flist[];
extern char		g_flist_name[14][4];

t_node			*io_redirect(t_token tok)
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
		node->f = g_flist[tok.type - LESS];
		bckp = g_alias_treated;
		g_alias_treated = 1;
		if (tok.type == DLESS || tok.type == DLESSDASH)
			node->right.c = here_end(gnt(NULL, 0));
		else
			node->right.c = filename(gnt(NULL, 0));
		g_alias_treated = bckp;
		if (!node->right.c && (g_parsingerr = 1))
			psherror(e_syntax_error,
							g_flist_name[tok.type - LESS], e_parsing_type);
		return (node);
	}
	return (NULL);
}
