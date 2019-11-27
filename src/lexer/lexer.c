/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 17:14:33 by abarthel         ###   ########.fr       */
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

char	*ft_quoted_word(char **str)
{
	int		i;
	int		a;
	int		b_slash;
	char	*tmp;

	i = 0;
	a = 0;
	b_slash = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
		{
			++b_slash;
			i += 2;
		}
		if ((*str)[i])
			++i;
	}
	i = i - b_slash;
	if (!(tmp = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while ((**str))
	{
		if ((**str) == '\\')
			(*str)++;
		tmp[a] = (**str);
		++a;
		(*str)++;
	}
	tmp[a] = '\0';
	return (tmp);
}

char	*ft_str_word(char **str)
{
	int		i;
	int		a;
	int		b_slash;
	char	*tmp;

	i = 0;
	a = 0;
	b_slash = 0;
	while ((*str)[i] != '\0' && ft_istoken(&(*str)[i]) == NONE && !ft_isspace((*str)[i])
			&& !ft_is_quote((*str)[i]))
	{
		if ((*str)[i] == '\\')
		{
			b_slash++;
			i += 2;
		}
		if ((*str)[i] != '\0')
			i++;
	}
	i = i - b_slash;
	if (!(tmp = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while ((**str) != '\0' && ft_istoken((*str)) == NONE && !ft_isspace((**str))
			&& !ft_is_quote((**str)))
	{
		if ((**str) == '\\')
			(*str)++;
		tmp[a] = (**str);
		a++;
		(*str)++;
	}
	tmp[a] = '\0';
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
			return (tokenization(WORD, ft_quoted_word(&index)));
		if (ft_isdigit(*index))
		{
			if (*(index + 1) == '<' || *(index + 1) == '>')
				return (tokenization(IO_NUMBER, ft_check_nbr(&index)));
		}
		if (ft_istoken(index) == NONE)
			if ((token = ft_assignment_word(index)))
				return (tokenization(token, ft_str_word(&index)));
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

char	**lexer(char **input)
{
	t_token	token;

	token = get_next_token(*input);
	ft_printf("_______________________________________________\n");
	ft_printf("token.symbol : %s\n", token.symbol);
	ft_printf("token.type : %d = %s\n", token.type, get_token_symbol(token.type));
	while (token.type != E_EOF && token.type != E_ERROR)
	{
		token = get_next_token(NULL);
		ft_printf("_______________________________________________\n");
		ft_printf("token.symbol : %s\n", token.symbol);
		ft_printf("token.type : %d = %s\n", token.type, get_token_symbol(token.type));
	}
	ft_printf("_______________________________________________\n");

/*	gnt(NULL);
this should be a link between parser and lexer calling back and forth*/
	exit(0); /*debug*/
	return (input);
}
