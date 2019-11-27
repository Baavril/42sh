/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:52:12 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/27 15:53:58 by bprunevi         ###   ########.fr       */
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
	{ DLESS , "<<" },
	{ DGREAT, ">>" },
	{ LESSAND, "<&" },
	{ GREATAND, ">&" },
	{ LESSGREAT, "<>" },
	{ DLESSDASH, "<<-" },
	{ PIPE, "|" }, /* not shell grammar native */
	{ GREAT, ">" }, /* not shell grammar native */
	{ LESS, "<" }, /* not shell grammar native */
	{ CLOBBER, ">|" }, /* not shell grammar native */
	{ SEMI, ";" }, /* not shell grammar native */
	{ If, "if" },
	{ Then, "then" },
	{ Else, "else" },
	{ Elif, "elif" },
	{ Fi, "fi" },
	{ Lbrace, "{" },
	{ Rbrace, "}" },
	{ -1, NULL }
};
