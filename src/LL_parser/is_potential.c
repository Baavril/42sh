/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_potential.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:38:29 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/03 19:27:14 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int		is_potenti(t_token t, int e_node)
{
	if (e_node == N_PREFIX)
		return (is_potenti(t, N_REDIRECT) || is_potenti(t, N_ASSIGNMENT_WORD));
	if (e_node == N_SUFFIX)
		return (is_potenti(t, N_REDIRECT) || is_potenti(t, N_WORD));
	if (e_node == N_REDIRECT)
		return ((t.type >= LESS && t.type <= ANDGREAT) || t.type == IO_NUMBER);
	if (e_node == N_ASSIGNMENT_WORD)
		return (t.type == ASSIGNMENT_WORD);
	if (e_node == N_WORD)
		return (t.type == WORD || is_potenti(t, N_ASSIGNMENT_WORD));
	if (e_node == N_CMD_NAME)
		return (is_potenti(t, N_WORD));
	if (e_node == N_CMD_WORD)
		return (is_potenti(t, N_WORD));
	if (e_node == N_OR_IF)
		return (t.type == OR_IF);
	if (e_node == N_AND_IF)
		return (t.type == AND_IF);
	if (e_node == N_PIPE)
		return (t.type == PIPE);
	if (e_node == N_SEMI)
		return (t.type == SEMI);
	if (e_node == N_AND)
		return (t.type == AND);
	return (0);
}
