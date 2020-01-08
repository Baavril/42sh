/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_gnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:00:35 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/08 16:29:27 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokens.h"
#include "libft.h"
#include "expansions.h"

static t_token *tokendup(t_token tok)
{
	t_token *rtn;

	rtn = malloc(sizeof(t_token));
	rtn->symbol = tok.symbol;
	ft_printf("[%s]\n", tok.symbol);
	rtn->type = tok.type;
	return(rtn);
}

static void		fill_stack(t_list **stack)
{
	char **tmp1;
	char **tmp2;
	t_token tok;

	tmp1 = NULL;
	tok = get_next_token(NULL);
	if (tok.type == WORD && !ft_strcmp(tok.symbol, "*"))
	{
		tmp1 = ft_strsplit(tok.symbol, "/");
		tmp2 = ft_globing(tmp1);
		ft_tabdel(&tmp1);
		tmp1 = tmp2;
		while (*tmp1)
		{
			tok.symbol = *tmp1;
			tok.type = WORD;
			ft_lstadd(stack, ft_lstnew(tokendup(tok), sizeof(t_token)));
			tmp1++;
		}
		ft_printf("...%p\n", tmp2);
		free(tmp2);
	}
	else
		ft_lstadd(stack, ft_lstnew(tokendup(tok), sizeof(t_token)));
}

t_token	gnt(char *future)
{
	static t_list *stack = NULL;
	t_list *tmp_stack = NULL;
	t_token tmp_tok;

	if (!stack)
		fill_stack(&stack);
	tmp_tok = *((t_token *)stack->content);
	if (!future)
	{
		tmp_stack = stack->next;
		free(stack->content);
		//ft_printf("---%p\n", tmp_tok.symbol);
		//free(tmp_tok.symbol);
		//ft_printf("---bravo\n");
		free(stack);
		stack = tmp_stack;
	}
	ft_printf("%s - %s\n",future,  tmp_tok.symbol);
	return(tmp_tok);
}

t_token peek()
{
	return (gnt("future"));
}
