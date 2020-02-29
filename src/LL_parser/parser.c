/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:29:21 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 13:47:11 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
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
	tok = eat();
	if (!g_parsingerr && ast)
		ast->f(ast->left, ast->right);
	g_parsingerr = 0;
	while (tok.type != E_EOF)
	{
		ft_strdel(&tok.symbol);
		tok = eat();
	}
	astdel(ast);
	ast = NULL;
}
