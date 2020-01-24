
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:52:12 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/14 15:03:05 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tokens.h"

/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */

struct s_token	g_grammar_symbols[] =
{
	{ AND_IF, "&&" },
	{ OR_IF, "||" },
	{ CLOBBER, ">|" },
	{ DLESSDASH, "<<-" },
	{ DLESS , "<<" },
	{ DGREAT, ">>" },
	{ LESSAND, "<&" },
	{ GREATAND, ">&" },
	{ LESSGREAT, "<>" },
	{ PIPE, "|" },
	{ AND, "&" },
	{ GREAT, ">" },
	{ LESS, "<" },
	{ SEMI, ";" },
	{ If, "if" },
	{ Then, "then" },
	{ Else, "else" },
	{ Elif, "elif" },
	{ Fi, "fi" },
//	{ Lbrace, "{" },
//	{ Rbrace, "}" },
	{ -1, NULL }
};
