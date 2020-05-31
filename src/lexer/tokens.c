/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:34:42 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/30 20:43:42 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

void				*cpy_without_bn(void *dst, const void *src, size_t n)
{
	int				op_q;
	size_t			i;
	size_t			y;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	i = 0;
	y = 0;
	op_q = 0;
	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	while (i < n)
	{
		if (p_src[i] == '\'')
			op_q ^= 1;
		if (p_src[i] == '\\' && p_src[i + 1] == '\n' && !op_q)
			i += 2;
		p_dst[y++] = p_src[i];
		i++;
	}
	return (dst);
}

static int			get_token_type(char *str)
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

int					ft_istoken(char *str)
{
	int	tok_type;

	tok_type = get_token_type(str);
	if (tok_type == -1)
		return (NONE);
	return (tok_type);
}
