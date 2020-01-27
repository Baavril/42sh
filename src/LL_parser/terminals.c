/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 09:38:27 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/27 11:39:58 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "expansions.h"
#include "libft.h"

char	*word(t_token tok)
{
	if (tok.type == WORD || tok.type == ASSIGNMENT_WORD)
	{
		//expansions_treatment(&tok.symbol);
		return(tok.symbol);
	}
	return(NULL);
}

char	*assig_word(t_token tok)
{
	if (tok.type == ASSIGNMENT_WORD)
	{
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

