/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_potential.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:38:29 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 15:25:32 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int		is_potential(t_token tok, int e_node)
{
	if (e_node == N_PREFIX)
		return (is_potential(tok, N_REDIRECT) || is_potential(tok, N_ASSIGNMENT_WORD));
	if (e_node == N_SUFFIX)
		return (is_potential(tok, N_REDIRECT) || is_potential(tok, N_WORD));
	if (e_node == N_REDIRECT)
		return ((tok.type >= LESS && tok.type <= ANDGREAT) || tok.type == IO_NUMBER);
	if (e_node == N_ASSIGNMENT_WORD)
		return (tok.type == ASSIGNMENT_WORD);
	if (e_node == N_WORD)
		return (tok.type == WORD || is_potential(tok, N_ASSIGNMENT_WORD));
	if (e_node == N_CMD_NAME)
		return (is_potential(tok, N_WORD));
	if (e_node == N_CMD_WORD)
		return (is_potential(tok, N_WORD));
	if (e_node == N_OR_IF)
		return (tok.type == OR_IF);
	if (e_node == N_AND_IF)
		return (tok.type == AND_IF);
	if (e_node == N_PIPE)
		return (tok.type == PIPE);
	if (e_node == N_SEMI)
		return (tok.type == SEMI);
	if (e_node == N_AND)
		return (tok.type == AND);
	return (0);
}
