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
	{ PIPE, "|" }, /* naaaaaaaaaaaann, code rampage XD */
	{ If, "if" },
	{ Then, "then" },
	{ Else, "else" },
	{ Elif, "elif" },
	{ Fi, "fi" },
	{ Lbrace, "{" },
	{ Rbrace, "}" },
	{ -1, NULL }
};
