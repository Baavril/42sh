/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by bprunevi          #+#    #+#             */
/*   Updated: 2020/07/07 16:25:38 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "lexer.h"

char				*advance(char *tmp, char **index)
{
	int	i;

	i = 0;
	if (tmp == NULL)
		return (NULL);
	while ((*index)[0] == '\\' && (*index)[1] == '\n')
		*index += 2;
	while (tmp[i] != '\0')
	{
		(*index)++;
		i++;
	}
	return (tmp);
}

char				*ft_get_word(char **str)
{
	char	*tmp;
	char	quote_type;
	_Bool	open_quotes;
	int		i;

	i = 0;
	open_quotes = 0;
	quote_type = -3;
	ft_quote(str, &i, quote_type, open_quotes);
	if (!(tmp = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	tmp = (char*)cpy_without_bn((void*)tmp, (void*)(*str), i);
	*str += i;
	return (tmp);
}

static char			*ft_check_nbr(char **nbr)
{
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * 2)))
		return (NULL);
	tmp[0] = (**nbr);
	tmp[1] = '\0';
	(*nbr)++;
	return (tmp);
}

static int			ft_assignment_word(char *str)
{
	if (*str == '=')
		return (WORD);
	while ((*str) != '\0' && ft_istoken(str) == NONE
			&& !ft_isspace((*str)) && !ft_is_quote((*str)))
	{
		if (*str == '=')
			return (ASSIGNMENT_WORD);
		str++;
	}
	return (WORD);
}

t_token				ft_delimit_token(char **index)
{
	int				token;
	char			*tmp;

	while (ft_isspace(**index))
		++(*index);
	while (**index)
	{
		if (ft_is_quote(**index))
			return (tokenization(WORD, ft_get_word(index)));
		if (ft_isdigit(**index))
		{
			if ((*index)[1] == '<' || ((*index)[1]) == '>')
				return (tokenization(IO_NUMBER, ft_check_nbr(index)));
		}
		if (ft_istoken(*index) == NONE)
			if ((token = ft_assignment_word(*index)))
				return (tokenization(token, ft_get_word(index)));
		if ((token = ft_istoken(*index)) != NONE)
		{
			tmp = get_token_symbol(token);
			return (tokenization(token, advance(tmp, index)));
		}
		return (tokenization(E_ERROR, NULL));
	}
	return (tokenization(E_EOF, "EOF"));
}
