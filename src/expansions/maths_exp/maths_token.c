/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:06:14 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/12 11:16:44 by tgouedar         ###   ########.fr       */
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

void			ft_free_token(void *content, size_t size)
{
	t_maths_token	*token;

	(void)size;
	token = (t_maths_token*)content;
	ft_strdel(&(token->token));
	ft_memdel(&content);
}
