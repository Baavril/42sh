/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/15 12:56:24 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "tokens.h"

/* ------------------------------------------------------
**               FILE: lexer_utils.c
** ------------------------------------------------------
*/

int	ft_istoken(char *str);

int		ft_is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int ft_is_op_bracket(char c)
{
	return (c == '{' || c == '(');
}

static int ft_is_close_bracket(char c)
{
	return (c == '}' || c == ')');
}

char		*advance(char *tmp, char **index)
{
	int	i;

	i = 0;
	if (tmp == NULL)
		return (NULL);
	while (tmp[i] != '\0')
	{
		(*index)++;
		i++;
	}
	return (tmp);
}

char	*ft_get_word(char **str)
{
	char	*tmp;
	int	i;
	char	quote_type;
	_Bool	open_quotes;

	i = 0;
	open_quotes = 0;
	while ((*str)[i])
	{
			if (!open_quotes && (ft_is_quote((*str)[i]) || ft_is_op_bracket((*str)[i])))
			{
				open_quotes ^= 1;
				quote_type = (*str)[i]; //Initialisation optionelle, cree des erreurs !
				++i;
				continue;
			}
			if (!open_quotes && (ft_istoken(&(*str)[i]) || ft_isspace((*str)[i])))
			{
				break;
			}
			if ((*str)[i] == quote_type || ft_is_close_bracket((*str)[i]))
			{
				++i;
				open_quotes ^= 1;
				continue;
			}
			if ((*str)[i] == '\\' &&
				((open_quotes && quote_type != '\'') || !open_quotes))
				++i;
			++i;
	}
	if (!(tmp = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	tmp = (char*)ft_memcpy((void*)tmp, (void*)(*str), i);
	*str += i;
	return (tmp);
}

char	*ft_check_nbr(char **nbr)
{
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * 2)))
		return (NULL);
	tmp[0] = (**nbr);
	tmp[1] = '\0';
	(*nbr)++;
	return (tmp);
}

/* ------------------------------------------------------
**               FILE: get_next_token.c
** ------------------------------------------------------
*/

static int	get_token_type(char *str)
{
	int	i;

	i = 0;
	while (g_grammar_symbols[i].type != -1)
	{
		if (!ft_strncmp(g_grammar_symbols[i].symbol, str, ft_strlen(g_grammar_symbols[i].symbol)))
			return (g_grammar_symbols[i].type);
		++i;
	}
	return (-1);
}

int	ft_istoken(char *str)
{
	int	tok_type;

	tok_type = get_token_type(str);
	if (tok_type == -1)
		return (NONE);
	return (tok_type);
}

static int		ft_assignment_word(char *str)
{
	if (*str == '=')
		return (WORD);
	while ((*str) != '\0' && ft_istoken(str) == NONE && !ft_isspace((*str)) && !ft_is_quote((*str)))
	{
		if (*str == '=')
			return (ASSIGNMENT_WORD);
		str++;
	}
	return (WORD);
}

static char	*get_token_symbol(int token)
{
	int	i;

	i = 0;
	while (g_grammar_symbols[i].type != -1)
	{
		if (g_grammar_symbols[i].type == token)
			return (g_grammar_symbols[i].symbol);
		++i;
	}
	return (NULL);
}


static t_token	tokenization(char type, char *value)
{
	t_token	token;

	if (value == NULL)
	{
		token.type = E_ERROR;
		token.symbol = NULL;
		return (token);
	}
	token.type = type;
	token.symbol = &value[0];
	return (token);
}

t_token	get_next_token(char *str)
{
	static char	*index;
	int		token;
	char		*tmp;

	if (str)
		index = str;
	while (ft_isspace(*index))
		++index;
	while (*index)
	{
		if (ft_is_quote(*index))
			return (tokenization(WORD, ft_get_word(&index)));
		if (ft_isdigit(*index))
		{
			if (*(index + 1) == '<' || *(index + 1) == '>')
				return (tokenization(IO_NUMBER, ft_check_nbr(&index)));
		}
		if (ft_istoken(index) == NONE)
			if ((token = ft_assignment_word(index)))
				return (tokenization(token, ft_get_word(&index)));
		if ((token = ft_istoken(index)) != NONE)
		{
			tmp = get_token_symbol(token);
			return (tokenization(token, advance(tmp, &index)));
		}
		return (tokenization(E_ERROR, NULL));
	}
	return (tokenization(E_EOF, "EOF"));
}

/* ------------------------------------------------------
**               FILE: lexer.c
** ------------------------------------------------------
*/

char	**lexer_verbose(char **input)
{
	t_token	token;

	token = get_next_token(*input);
	ft_dprintf(2, "_______________________________________________\n");
	ft_dprintf(2, "token.symbol : %s\n", token.symbol);
	ft_dprintf(2, "token.type : %d = %s\n", token.type, get_token_symbol(token.type));
	while (token.type != E_EOF && token.type != E_ERROR)
	{
		token = get_next_token(NULL);
		ft_dprintf(2, "_______________________________________________\n");
		ft_dprintf(2, "token.symbol : %s\n", token.symbol);
		ft_dprintf(2, "token.type : %d = %s\n", token.type, get_token_symbol(token.type));
	}
	ft_dprintf(2, "_______________________________________________\n");
	return (input);
}
