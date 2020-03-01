/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:04:47 by baavril           #+#    #+#             */
/*   Updated: 2020/03/01 17:09:43 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "libft.h"
#include "input.h"
#include "prompt.h"
#include "display.h"
#include "history.h"

#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdint.h>

int			set_reader(union u_tc *term, char **buff, t_cursor *cursor)
{
	if (cursor->ctrl_r)
	{
		ft_strdel(&(cursor->prompt));
		cursor->prompt_len = search_prompt(cursor, *buff);
		cursor->end = ft_strlen(cursor->match);
		display(cursor->match, cursor);
		cursor->end = ft_strlen(*buff);
		return (0);
	}
	display(*buff, cursor);
	ft_bzero(term->buff, ft_strlen(term->buff));
	return (1);
}

int			standard_analyzer(union u_tc *term, char **buff, t_cursor *cursor)
{
	keyboard_ctrl_c(term, buff, cursor);
	keyboard_ctrl_d(term, buff, cursor);
	keyboard_ctrl_l(term, buff, cursor);
	keyboard_normal_char(term, buff, cursor);
	keyboard_backspace(term, buff, cursor);
	keyboard_tabulation(term, buff, cursor);
	if (keyboard_dispatcher(term, buff, cursor) == 0
	|| !keyboard_enter(term, buff, cursor))
		return (0);
	set_reader(term, buff, cursor);
	return (1);
}

int			search_analyzer(union u_tc *term, char **buff, t_cursor *cursor)
{
	if (!cursor->ctrl_r)
	{
		ft_bzero(*buff, ft_strlen(*buff));
		ft_strdel(&(cursor->prompt));
		ft_init_cursor(cursor);
		cursor->ctrl_r = 1;
	}
	keyboard_normal_char(term, buff, cursor);
	keyboard_backspace(term, buff, cursor);
	if (!(keyboard_enter(term, buff, cursor)))
		return (0);
	else if (keyboard_tabulation(term, buff, cursor) == 0
	|| keyboard_ctrl_l(term, buff, cursor) == 0
	|| keyboard_dispatcher(term, buff, cursor) >= 0)
	{
		cursor->on = 0;
		cursor->ctrl_r = 0;
		set_reader(term, buff, cursor);
		return (1);
	}
	cursor->on = 1;
	set_reader(term, buff, cursor);
	return (-1);
}

int			analyzer(t_cursor *cursor, char **buff, union u_tc *term)
{
	if (term->key == CTRL_R || cursor->on == 1)
	{
		if (!(search_analyzer(term, buff, cursor)))
			return (0);
	}
	else if (cursor->on == 0)
	{
		if (!(standard_analyzer(term, buff, cursor)))
			return (0);
	}
	return (1);
}
