/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 09:38:27 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/27 14:22:29 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"

char	*word(t_token tok)
{
	if (tok.type == WORD || tok.type == ASSIGNMENT_WORD)
	{
		ft_printf("tok.type of type WORD detected with value '%s' !\n", tok.symbol);
		return(tok.symbol);
	}
	return(NULL);
}

char	*assig_word(t_token tok)
{
	if (tok.type == ASSIGNMENT_WORD)
	{
		ft_printf("tok.type of type ASSIG_WORD detected with value '%s' !\n", tok.symbol);
		return(tok.symbol);
	}
	return(NULL);
}

char	*io_number(t_token tok)
{
	if (tok.type == IO_NUMBER)
	{
		return(tok.symbol);
	}
	return(NULL);
}

