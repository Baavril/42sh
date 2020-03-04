/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 10:56:01 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/01 11:09:51 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "keys.h"

void		update_buff(char **buff, t_cursor *cursor)
{
	size_t len;

	len = 0;
	ft_bzero(*buff, ft_strlen(*buff));
	if (cursor->match)
	{
		len = ft_strlen(cursor->match);
		if (cursor->end < len)
			*buff = buff_realloc(*buff, len);
		ft_strcpy(*buff, cursor->match);
	}
	cursor->end = len;
}
