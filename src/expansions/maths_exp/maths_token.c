/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:06:14 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/09 21:30:50 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "maths_interne.h"

t_maths_token	*ft_init_maths_token(char *word, size_t token_len, char flag)
{
	t_maths_token	*new;

	/*ft_check_memory(*/new = malloc(sizeof(*new));
	/*ft_check_memory(*/new->token = ft_strndup(word, token_len);
	if (flag == IS_OP)
		new->prio = ft_get_op_priority(new->token);
	else
		new->prio = 0;
	return (new);
}
