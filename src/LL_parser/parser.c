/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:29:21 by yberramd          #+#    #+#             */
/*   Updated: 2020/03/01 18:52:35 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokens.h"
#include "jcont.h"

extern int	g_parsingerr;
extern int	g_prefix;

void	execute(char *input)
{
	t_node	*ast;
	t_token	tok;

	g_parsingerr = 0;
	g_prefix = 0;
	ast = comp_list(gnt(input, 0));
	tok = gnt(NULL, 0);
	if (tok.type != E_EOF)
		ft_printf("parsing error\n");
	else if (!g_parsingerr && ast)
		ast->f(ast->left, ast->right);
	g_parsingerr = 0;
	while (tok.type != E_EOF)
	{
		if (tok.type == WORD)
			ft_strdel(&tok.symbol);
		tok = gnt(NULL, 0);
	}
	astdel(ast);
	ast = NULL;
}
