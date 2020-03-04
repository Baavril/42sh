/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:35:41 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 14:44:34 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "keys.h"
#include "history.h"

int			right_arrow(char **buff, t_cursor *cursor)
{
	(void)buff;
	if (cursor->start < cursor->end)
		++(cursor->start);
	return (1);
}

int			left_arrow(char **buff, t_cursor *cursor)
{
	(void)buff;
	if (cursor->start > 0)
		--(cursor->start);
	return (1);
}

int			down_arrow(char **buff, t_cursor *cursor)
{
	char *str;

	str = NULL;
	if (!g_inside_history)
		return (1);
	else if (history(FORWARD, NULL, &str) == 2)
	{
		set_string(buff, cursor, g_inside_history);
		ft_strdel(&g_inside_history);
	}
	else
		set_string(buff, cursor, str);
	return (1);
}

int			up_arrow(char **buff, t_cursor *cursor)
{
	char *str;

	str = NULL;
	if (!g_inside_history && (g_inside_history = ft_strdup(*buff)))
		history(LAST, NULL, &str);
	else
		history(BACKWARD, NULL, &str);
	set_string(buff, cursor, str);
	return (1);
}
