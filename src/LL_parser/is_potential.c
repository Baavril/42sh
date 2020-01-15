/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_potential.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:38:29 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/15 12:01:48 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

/* is_potential renvoie 1 si il est susceptible d'etre
 * le premier element d'un regle e_node, sinon 0
 * Exemple : WORD peut etre le premier element d'un PREFIX
 * PIPE ne peut pas etre le premier element d'un SUFFIX
 */
int		is_potential(t_token tok, int e_node)
{
	if (e_node == N_PREFIX)
		return(is_potential(tok, N_REDIRECT) || is_potential(tok, N_ASSIGNMENT_WORD));
	if (e_node == N_SUFFIX)
		return(is_potential(tok, N_REDIRECT) || is_potential(tok, N_WORD));
	if (e_node == N_REDIRECT)
		return (( tok.type >= LESS
			   && tok.type <= CLOBBER)
			   || tok.type == IO_NUMBER);
	if (e_node == N_ASSIGNMENT_WORD)
		return(tok.type == ASSIGNMENT_WORD);
	if (e_node == N_WORD)
		return(tok.type == WORD || is_potential(tok, N_ASSIGNMENT_WORD));
	if (e_node == N_CMD_NAME)
		return(is_potential(tok, N_WORD));
	if (e_node == N_CMD_WORD)
		return(is_potential(tok, N_WORD));
	if (e_node == N_PIPE)
		return(tok.type == PIPE);
	if (e_node == N_SEMI)
		return(tok.type == SEMI);
	if (e_node == N_AND)
		return(tok.type == AND);
	return(0);
}
