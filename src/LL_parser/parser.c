/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:29:21 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/26 12:50:07 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "jcont.h"

extern int g_parsingerr;

void	execute(char *input)
{
	t_node *AST;
	t_token tok;

	g_parsingerr = 0;
	AST = comp_list(gnt(input, 0));
	tok = eat();
	if (!g_parsingerr && AST)
		AST->f(AST->left, AST->right);
	g_parsingerr = 0;
	while (tok.type != E_EOF)
	{
		ft_strdel(&tok.symbol);
		tok = eat();
	}
	astdel(AST);
	AST = NULL;
}
