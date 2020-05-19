/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 18:44:46 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/19 13:10:52 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token				tokenization(char type, char *value)
{
	t_token	token;

	if (value == NULL)
	{
		token.type = E_ERROR;
		token.symbol = NULL;
		return (token);
	}
	token.type = type;
	token.symbol = &value[0];
	return (token);
}

void				ft_free_token(t_token *token)
{
	if (token)
		if (token->type == WORD || token->type == ASSIGNMENT_WORD
		|| token->type == NAME || token->type == IO_NUMBER)
			if (token->symbol)
				free(token->symbol);
}

t_token				get_next_token_alias(char *str)
{
	static char		*index;

	if (str)
		index = str;
	return (ft_delimit_token(&index));
}

t_token				get_next_token(char *str)
{
	static char		*index;

	if (str)
		index = str;
	return (ft_delimit_token(&index));
}

char				*get_token_symbol(int token)
{
	int	i;

	i = 0;
	while (g_grammar_symbols[i].type != -1)
	{
		if (g_grammar_symbols[i].type == token)
			return (g_grammar_symbols[i].symbol);
		++i;
	}
	return (NULL);
}
