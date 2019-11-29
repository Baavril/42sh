/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:51:38 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/29 10:37:59 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
#define TOKENS_H
/* -------------------------------------------------------
   The token types
   ------------------------------------------------------- */

enum e_tokens
{
	NONE, /* not shell grammar native */
	E_ERROR, /* not shell grammar native */
	E_EOF, /* not shell grammar native */
	PIPE, /* not shell grammar native */
	GREAT, /* not shell grammar native */
	LESS, /* not shell grammar native */
	CLOBBER, /* not shell grammar native */
	SEMI, /* not shell grammar native */

	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,

/* The following are the operators (see XBD Operator)
   containing more than one character. */

	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,

/* The following are the reserved words. */

	If,
	Then,
	Else,
	Elif,
	Fi,

/* These are reserved words, not operator tokens, and are
   recognized when reserved words are recognized. */

	Lbrace,
	Rbrace
};

enum e_nodes
{
	N_SUFFIX,
	N_PREFIX,
	N_REDIRECT,
	N_WORD,
	N_CMD_NAME,
	N_CMD_WORD,
	N_ASSIGNMENT_WORD,
	N_PIPE,
	N_SEMI,
};

struct s_token
{
	int	type;
	char	*symbol;
};

typedef struct s_token	t_token;

extern struct s_token	g_grammar_symbols[];
#endif
