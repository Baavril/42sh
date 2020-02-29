/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:52:12 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 19:46:10 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tokens.h"

struct s_token	g_grammar_symbols[] =
{
	{ AND_IF, "&&" },
	{ OR_IF, "||" },
	{ CLOBBER, ">|" },
	{ DLESSDASH, "<<-" },
	{ DLESS, "<<" },
	{ DGREAT, ">>" },
	{ LESSAND, "<&" },
	{ GREATAND, ">&" },
	{ ANDGREAT, "&>" },
	{ LESSGREAT, "<>" },
	{ PIPE, "|" },
	{ AND, "&" },
	{ GREAT, ">" },
	{ LESS, "<" },
	{ SEMI, ";" },
	{ -1, NULL }
};
