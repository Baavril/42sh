/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_copypaste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:40:05 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 14:57:24 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "input.h"

#include <stdint.h>

int			paste_key(char **buff, t_cursor *cursor)
{
	char *str;

	str = g_copybuff;
	if (str)
		while (*str)
			normal_char(buff, cursor, *str++);
	return (1);
}

int			select_key(char **buff, t_cursor *cursor)
{
	if (cursor->in == SIZE_MAX)
		cursor->in = cursor->start;
	else if (cursor->in != cursor->start)
	{
		ft_strdel(&g_copybuff);
		if (cursor->start > cursor->in)
			g_copybuff = ft_strndup(*buff + cursor->in,
					cursor->start - cursor->in);
		else if (cursor->start < cursor->in)
			g_copybuff = ft_strndup(*buff + cursor->start,
					cursor->in - cursor->start);
		cursor->in = SIZE_MAX;
	}
	return (1);
}

int			delete_key(char **buff, t_cursor *cursor)
{
	if (cursor->start < cursor->end && cursor->end > 0)
	{
		ft_memmove(&((*buff)[cursor->start]), &((*buff)[cursor->start + 1]),
				cursor->end - cursor->start);
		--(cursor->end);
	}
	return (1);
}

int			backspace_key(char **buff, t_cursor *cursor)
{
	if (cursor->end > 0 && cursor->start > 0)
	{
		--(cursor->start);
		ft_memmove(&((*buff)[cursor->start]), &((*buff)[cursor->start + 1]),
				cursor->end - cursor->start);
		--(cursor->end);
	}
	return (1);
}
