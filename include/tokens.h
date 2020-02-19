/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:51:38 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/19 12:26:04 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/* -------------------------------------------------------
**                   The token types
** -------------------------------------------------------
*/

enum					e_tokens
{
	NONE,
	E_ERROR,
	E_EOF,
	PIPE,
	SEMI,
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,
	AND_IF,
	OR_IF,
	AND,

/* The following are the redirect operators */

	LESS,
	DLESS,
	LESSAND,
	GREAT,
	DGREAT,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	CLOBBER,

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

enum					e_nodes
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
	N_AND,
	N_AND_IF,
	N_OR_IF,
};

struct					s_token
{
	int					type;
	char				*symbol;
};

typedef struct s_token	t_token;

extern struct s_token	g_grammar_symbols[];

#endif
