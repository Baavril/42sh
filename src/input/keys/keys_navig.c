/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_navig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:38:42 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 14:40:07 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

int			home_key(char **buff, t_cursor *cursor)
{
	(void)buff;
	cursor->start = 0;
	return (1);
}

int			end_key(char **buff, t_cursor *cursor)
{
	(void)buff;
	cursor->start = cursor->end;
	return (1);
}

int			next_word(char **buff, t_cursor *cursor)
{
	while (cursor->start < cursor->end && ft_isalnum((*buff)[cursor->start]))
		(cursor->start)++;
	while (cursor->start < cursor->end && !ft_isalnum((*buff)[cursor->start]))
		(cursor->start)++;
	return (1);
}

int			previous_word(char **buff, t_cursor *cursor)
{
	while (cursor->start > 0 && ft_isalnum((*buff)[cursor->start]))
		(cursor->start)--;
	while (cursor->start > 0 && !ft_isalnum((*buff)[cursor->start]))
		(cursor->start)--;
	return (1);
}
