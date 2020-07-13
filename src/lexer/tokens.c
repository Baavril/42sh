/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:34:42 by yberramd          #+#    #+#             */
/*   Updated: 2020/07/13 13:24:50 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

char				*cpy_without_bn(char *dst, const char *src, int n)
{
	char	quote_t;
	_Bool	open_q;
	int			i;
	int			j;
	int			y;

	i = 0;
	j = 0;
	y = 0;
	open_q = 0;
	quote_t = -3;
	while (i < n)
	{
		ft_quote_tic(src, &i, &quote_t, &open_q);
		while (j < i)
		{
			while (!(open_q && quote_t == '\'')
			&& src[j] == '\\' && src[j + 1] == '\n')
				j += 2;
			dst[y++] = src[j++];
		}
	}
	return (dst);
}

static int			get_token_type(const char *str)
{
	int	i;

	i = 0;
	while (g_grammar_symbols[i].type != -1)
	{
		if (!ft_strncmp(g_grammar_symbols[i].symbol,
					str, ft_strlen(g_grammar_symbols[i].symbol)))
			return (g_grammar_symbols[i].type);
		++i;
	}
	return (-1);
}

int					ft_istoken(const char *str)
{
	int		i;
	int		tok_type;

	i = 0;
	while (str[i] == '\\' && str[i + 1] == '\n' && str[i + 2])
		i += 2;
	tok_type = get_token_type(str + i);
	if (tok_type == -1)
		return (NONE);
	return (tok_type);
}
