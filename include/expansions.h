/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/15 16:36:15 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include <stddef.h>

# define STAR '*'
# define AROB '@'
# define EXCLAM '!'
# define OP_PAR '('
# define CL_PAR ')'
# define OP_SQUAR '['
# define CL_SQUAR ']'

# define SPC ' '
# define WHY '?'
# define PLUS '+'
# define DASH '-'
# define EQUAL '='
# define MINUS '-'
# define SLASH '/'
# define CARET '^'
# define SHARP '#'
# define TILDE '~'
# define AMPER '&'
# define COLON ':'
# define DOLLAR '$'
# define BSLASH '\\'
# define PERCENT '%'
# define DQUOTES '"'
# define SQUOTES '\''
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
# define MATHS_EXP 13

typedef struct	s_symexp
{
	int			sym;
	int			(*expand)(char **);
}				t_symexp;

typedef struct	s_expand
{
	int			j;
	int			nb;
	int			type;
	char		*tmp;
	char		*btw;
	char		*ptm;
	char		*keep;
	char		**tokens;
}				t_expand;

typedef struct	s_deploy
{
	int			i;
	int			j;
	int			flag;
	int			dash;
	char		*keep;
	char		*tmp;
	char		*ptm;
	char		*range;
}				t_deploy;

typedef struct	s_glob
{
	int			i;
	int			x;
	int			n;
	int			j;
	int			diff;
	char		c;
}				t_glob;

int				expansions_treatment(char **tokens);

int				direct_exp(char **token);
int				simple_exp(char **token);
int				why_exp(char **token);
int				plus_exp(char **token);
int				dash_exp(char **token);
int				equal_exp(char **token);
int				bsharp_exp(char **token);
int				osharp_exp(char **token);
int				dsharp_exp(char **token);
int				opercent_exp(char **token);
int				dpercent_exp(char **token);
int				maths_exp(char **token);
int				tilde_exp(char **token);

int				ft_strpchr(char *str, char c);
size_t			maths_len(char *token);

char			**ft_expsplit(char *str, char c);
char			*ft_setbslash(char *tokens, int nb);
int				ft_back_slashed(char **tokens);
char			*ft_set_slashed(char **tokens);
char			*ft_getbtw(char *tokens, int type);
char			*ft_quoted(char *tokens);
char			*ft_unset_quoted(char *tokens, char c);

int				identifier(char *token);

char			**ft_globing(char **split, char *token);

int				check_braces(char *token);
int				check_colon(char *token);
int				check_colon_symbol(char *token);
int				check_symbol(char *token);
int				check_maths(char *token);

int				check_next_var(char *var, char **token, int flag);
char			*ft_strcdup(char *token, char c);
char			*setasvar(char *token);
char			*ft_strrev(char *token);
char			*matching_ret(char *token, char *match, int flag);
char			*pattern_matching(char *token, char *match, int flag);
int				ft_spechrlen(char *token);
int				check_deploy(char *str, char *match, int flag, int star);

int				star_deployement(t_glob *var, char *match, char *str, int flag);
int				star_no_deployement(t_glob *var, char *match, char *str, int flag);
int				reach_star_flag(t_glob *var, char *match, char *str, int flag);
int				fixing_star_flag(t_glob *var, char *match, char *str, int flag);
int				reach_next_star_flag(t_glob *var, char *match, char *str, int flag);
int				positionning_star_flag(t_glob *var, char *match, char *str);
int				get_deploy(char **match);

char			*ft_alpharange(char c, char x);
char			*ft_strneg(char *match);

#endif
