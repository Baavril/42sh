/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_gnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:00:35 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/27 14:00:34 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokens.h"
#include "libft.h"

t_token	gnt(char *future)
{
	static t_token peek = {0, NULL};
	t_token tok;

	if (future && !peek.type)
	{
		peek = get_next_token(NULL);
		return(peek);
	}
	else if (future && peek.type)
		return (peek);
	else if (!future && peek.type)
	{
		tok = peek;
		peek.type = 0;
		peek.symbol = NULL;
	}
	else
	{
		tok = get_next_token(NULL);
		peek.type = 0;
		peek.symbol = NULL;
	}
	return(tok);
}

t_token peek()
{
	return (gnt("future"));
}
