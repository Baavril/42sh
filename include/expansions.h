/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/09 11:47:27 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# define STAR '*'
# define AROB '@'
# define EXCLAM '!'
# define OP_SQUAR '['
# define CL_SQUAR ']'

# define SPC ' '
# define WHY '?'
# define PLUS '+'
# define DASH '-'
# define SLASH '/'
# define EQUAL '='
# define CARET '^'
# define SHARP '#'
# define AMPER '&'
# define COLON ':'
# define DOLLAR '$'
# define BSLASH '\\'
# define PERCENT '%'
# define DQUOTES '"'
# define OP_BRACE '{'
# define CL_BRACE '}'
# define UNDERSCORE '_'

# define EMPTY_STR ""
# define MAXCHR 95

# define ERROR -1
# define SUCCESS 0
# define DIRECT_EXP 1
# define SIMPLE_EXP 2
# define COMPLEX_EXP 3
# define WHY_EXP 4
# define PLUS_EXP 5
# define DASH_EXP 6
# define EQUAL_EXP 7
# define BSHARP_EXP 8
# define OSHARP_EXP 9
# define DSHARP_EXP 10
# define OPERCENT_EXP 11
# define DPERCENT_EXP 12

typedef struct	s_symexp
{
				int		sym;
				int		(*expand)(char **);
}				t_symexp;

int		expansions_treatment(char **tokens);

int		direct_exp(char **token);
int		simple_exp(char **token);
int		why_exp(char **token);
int		plus_exp(char **token);
int		dash_exp(char **token);
int		equal_exp(char **token);
int		bsharp_exp(char **token);
int		osharp_exp(char **token);
int		dsharp_exp(char **token);
int		opercent_exp(char **token);
int		dpercent_exp(char **token);

int	ft_strpchr(char *str, char c);

#endif
