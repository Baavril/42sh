/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:41:17 by tgouedar          #+#    #+#             */
/*   Updated: 2020/07/13 13:42:24 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void				ft_quote(const char *s, int *i)
{
	char	quote_t;
	_Bool	open_q;

	open_q = 0;
	quote_t = -3;
	while (s[*i])
	{
		if (ft_quote_check(s, i, &quote_t, &open_q))
			return ;
	}
}
