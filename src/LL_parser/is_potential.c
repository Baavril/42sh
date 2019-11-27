/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_potential.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:38:29 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/27 15:31:21 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int		is_potential(t_token tok, int i)
{
	// TEMPORAIRE. MOCHE.
	if (i == N_PREFIX)
		return(is_potential(tok, N_REDIRECT) || is_potential(tok, N_ASSIGNMENT_WORD));
	if (i == N_SUFFIX)
		return(is_potential(tok, N_REDIRECT) || is_potential(tok, N_WORD));
	if (i == N_REDIRECT)
		return (  tok.type == LESS
				|| tok.type == LESSAND
				|| tok.type == GREAT
				|| tok.type == GREATAND
				|| tok.type == DGREAT
				|| tok.type == LESSGREAT
				|| tok.type == CLOBBER
				|| tok.type == IO_NUMBER);
	if (i == N_ASSIGNMENT_WORD)
		return(tok.type == ASSIGNMENT_WORD);
	if (i == N_WORD)
		return(tok.type == WORD || is_potential(tok, N_ASSIGNMENT_WORD));
	if (i == N_CMD_NAME)
		return(is_potential(tok, N_WORD));
	if (i == N_CMD_WORD)
		return(is_potential(tok, N_WORD));
	if (i == N_WORD)
	if (i == N_PIPE)
		return(tok.type == PIPE);
	if (i == N_SEMI)
		return(tok.type == SEMI);
	return(0);
}
