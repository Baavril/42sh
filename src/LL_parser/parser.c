/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:29:21 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/25 12:15:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokens.h"
#include "jcont.h"

extern int	g_parsingerr;
extern int	g_prefix;

int	execute(char *input)
{
	t_node	*ast;
	t_token	tok;
	int rtn;

	g_parsingerr = 0;
	g_prefix = 0;
	rtn = 0;
	ast = comp_list(gnt(input, 0));
	tok = gnt(NULL, 0);
	if (tok.type != E_EOF)
		ft_dprintf(2, "parsing error\n");
	else if (!g_parsingerr && ast)
		ast->f(ast->left, ast->right);
	rtn = g_parsingerr + (tok.type != E_EOF); 
	g_parsingerr = 0;
	while (tok.type != E_EOF)
	{
		if (tok.type == WORD || tok.type == ASSIGNMENT_WORD)
			ft_strdel(&tok.symbol);
		tok = gnt(NULL, 0);
	}
	astdel(ast);
	ast = NULL;
	return (rtn);
}
