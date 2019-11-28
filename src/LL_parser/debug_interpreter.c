/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_interpreter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:44:12 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/28 10:17:04 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"

#if INTERPRETER_MODE == COMPILER
t_node	*comp_list(t_token tok)
{
	t_node	*node;
	t_node	*tmp1;
	t_node	*tmp2;

	if ((tmp1 = and_or(tok)))
	{
		if (is_potential(peek(), N_SEMI))
		{
			gnt(NULL);
			if ((tmp2 = comp_list(gnt(NULL))))
			{
				node = malloc(sizeof(t_node));
				node->left.v = tmp1;
				node->right.v = tmp2;
				node->f = NULL; //should be i_comp_list();
				ft_printf("comp_list full with 2 elems was created\n");
				return(node);
			}
		}
		return(tmp1);
	}
	return(NULL);
}

#elif INTERPRETER_MODE == INTERPRETER
t_node	*inter_list(t_token tok)
{
	t_node	*tmp1;

	while (is_potential(tok, N_SEMI))
		tok = gnt(NULL);
	tmp1 = and_or(tok);
	return(tmp1);
}
#endif

void	interpret(t_node *node)
{
	if (node)
		ft_printf("interpreting a command..\n");
	if (!node)
		ft_printf("interpreting empty string..\n");
	ft_printf("_______________________________________________\n");
}

void	debug_parser(char *input)
{
#if INTERPRETER_MODE == INTEPRETER
	t_node *node;
	
	node = inter_list(get_next_token(input));
	while (node)
	{
		interpret(node);
		node = inter_list(gnt(NULL));
	}
#elif INTERPRETER_MODE == COMPILER
	interpret(comp_list(get_next_token(input)));
#endif
	gnt(NULL);
}
