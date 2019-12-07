/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 09:38:27 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/02 14:03:47 by bprunevi         ###   ########.fr       */
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
		ft_printf("tok.type of type IO_NUMBER detected with value '%s' !\n", tok.symbol);
		return(tok.symbol);
	}
	return(NULL);
}

