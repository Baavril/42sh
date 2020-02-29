/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:58:25 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 18:40:09 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "globing.h"
#include "builtins.h"
#include "expansions.h"
#include "parser.h"

int				g_alias_treated = 0;

static void		ft_treat_token(t_list **stack, t_token *tok)
{
	char	**tmp1;
	char	**tmp2;

	tmp1 = NULL;
	if (tok->type == WORD && (!(ft_isin(OP_BRACE, tok->symbol)
	&& ft_isin(CL_BRACE, tok->symbol)))
	&& ((ft_isin('/', tok->symbol) && ft_isin(STAR, tok->symbol))
	|| ft_isin(STAR, tok->symbol)))
	{
		tmp1 = ft_strsplit(tok->symbol, "/");
		tmp2 = globing(tmp1, tok->symbol);
		ft_tabdel(&tmp1);
		tmp1 = tmp2;
		ft_strdel(&(tok->symbol));
		while (*tmp1)
		{
			tok->symbol = *tmp1;
			tok->type = WORD;
			ft_lstadd_back(stack, ft_lstnew(tok, sizeof(t_token)));
			tmp1++;
		}
		free(tmp2);
	}
	else
		ft_lstadd_back(stack, ft_lstnew(tok, sizeof(t_token)));
}

static int		ft_check_alias(t_list **stack, t_token *first)
{
	t_token	tok;
	char	*first_token;
	char	*alias;

	if (first->type == ASSIGNMENT_WORD)
		return (0);
	g_alias_treated = 1;
	if (first->type != WORD)
		return (0);
	first_token = first->symbol;
	if ((alias = ft_get_alias(first_token)))
	{
		ft_free_token(first);
		tok = get_next_token_alias(alias);
		while (1)
		{
			ft_treat_token(stack, &tok);
			tok = get_next_token_alias(NULL);
			if (tok.type == E_ERROR || tok.type == E_EOF)
				break ;
		}
		ft_strdel(&alias);
		return (1);
	}
	return (0);
}

static void		fill_stack(t_list **stack, char *input)
{
	t_token	tok;

	tok = get_next_token(input);
	if (!(g_alias_treated))
		if (ft_check_alias(stack, &tok))
			return ;
	ft_treat_token(stack, &tok);
}

t_token			gnt(char *input, int future)
{
	static t_list	*stack = NULL;
	t_list			*tmp_stack;
	t_token			tmp_tok;

	tmp_stack = NULL;
	if (g_parsingerr)
		return ((t_token){E_EOF, NULL});
	if (!stack)
		fill_stack(&stack, input);
	tmp_tok = *((t_token*)stack->content);
	if (!future)
	{
		tmp_stack = stack->next;
		free(stack->content);
		free(stack);
		stack = tmp_stack;
	}
	return (tmp_tok);
}
