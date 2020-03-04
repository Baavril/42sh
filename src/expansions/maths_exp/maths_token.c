/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:06:14 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/19 12:14:56 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "maths_expansion.h"

t_maths_token	ft_init_maths_token(char *word, size_t token_len, char flag)
{
	t_maths_token	new;

	new.token = ft_strndup(word, token_len);
	if (flag == IS_OP)
		new.prio = ft_get_op_priority(new.token);
	else
		new.prio = 0;
	return (new);
}

void			ft_free_maths_token(void *content, size_t size)
{
	t_maths_token	*token;

	(void)size;
	token = (t_maths_token*)content;
	ft_strdel(&(token->token));
	ft_memdel(&content);
}
