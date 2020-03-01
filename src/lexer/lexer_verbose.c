/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_verbose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:47:24 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 17:47:26 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

char				**lexer_verbose(char **input)
{
	t_token	token;

	token = get_next_token(*input);
	ft_dprintf(2, "_______________________________________________\n");
	ft_dprintf(2, "token.symbol : %s\n", token.symbol);
	ft_dprintf(2, "token.type : %d = %s\n", token.type,
			get_token_symbol(token.type));
	while (token.type != E_EOF && token.type != E_ERROR)
	{
		ft_free_token(&token);
		token = get_next_token(NULL);
		ft_dprintf(2, "_______________________________________________\n");
		ft_dprintf(2, "token.symbol : %s\n", token.symbol);
		ft_dprintf(2, "token.type : %d = %s\n", token.type,
				get_token_symbol(token.type));
	}
	ft_free_token(&token);
	ft_dprintf(2, "_______________________________________________\n");
	return (input);
}
