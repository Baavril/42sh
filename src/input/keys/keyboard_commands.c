/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:41:28 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/22 14:53:50 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "display.h"
#include "prompt.h"
#include "history.h"

int			keyboard_normal_char(union u_tc *term, char **buff, t_cursor *curs)
{
	if (ft_isprint(term->key))
	{
		if (curs->ctrl_r)
		{
			curs->start = ft_strlen(*buff);
			normal_char(buff, curs, term->key);
			curs->match = get_history(buff, curs);
			return (0);
		}
		normal_char(buff, curs, term->key);
		return (0);
	}
	return (1);
}

int			keyboard_tabulation(union u_tc *term, char **buff, t_cursor *cursor)
{
	if (term->key == TABULATION)
	{
		if (cursor->ctrl_r)
		{
			tab_key(buff, cursor);
			ft_strdel(&(cursor->prompt));
			cursor->prompt_len = mkprompt(&(cursor->prompt));
			history(RESET, buff, NULL);
			return (0);
		}
		if (!(tab_key(buff, cursor)))
			return (-1);
		return (0);
	}
	return (1);
}

int			keyboard_enter(union u_tc *term, char **buff, t_cursor *cursor)
{
	if (term->key == ENTER)
	{
		if (cursor->ctrl_r)
		{
			update_buff(buff, cursor);
			history(RESET, buff, NULL);
			return (0);
		}
		cursor->start = ft_strlen(*buff);
		display(*buff, cursor);
		return (0);
	}
	return (1);
}

int			keyboard_backspace(union u_tc *term, char **buff, t_cursor *cursor)
{
	if (term->key == BACKSPACE)
	{
		if (cursor->ctrl_r)
		{
			cursor->start = ft_strlen(*buff);
			backspace_key(buff, cursor);
			if (**buff)
				cursor->match = get_history(buff, cursor);
			else
			{
				cursor->match = NULL;
				cursor->match_ret = 1;
			}
			return (0);
		}
		backspace_key(buff, cursor);
		return (0);
	}
	return (1);
}
