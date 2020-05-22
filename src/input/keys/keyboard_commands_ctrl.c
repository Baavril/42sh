/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_commands_ctrl.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:13:16 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/22 16:34:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "jcont.h"
#include "input.h"
#include "error.h"
#include "prompt.h"

#include <term.h>
#include <curses.h>

extern int	g_retval;
extern int	g_input_mode;

int			keyboard_ctrl_l(union u_tc *term, char **buff, t_cursor *cursor)
{
	if (term->key == CTRL_L)
	{
		if (cursor->ctrl_r)
		{
			update_buff(buff, cursor);
			ft_strdel(&(cursor->prompt));
			cursor->prompt_len = mkprompt(&(cursor->prompt));
			cursor->start = ft_strlen(*buff);
			ft_putstr(tgetstr("ho", NULL));
			return (0);
		}
		ft_putstr(tgetstr("ho", NULL));
	}
	return (1);
}

static int	keyboard_ctrl_c_wiper(char **buff, t_cursor *cursor)
{
	ft_strdel(buff);
	ft_strdel(&(cursor->prompt));
	*buff = ft_strdup("");
	ft_init_cursor(cursor);
	ft_putchar('\n');
	cursor->prompt_len = mkprompt(&(cursor->prompt));
	ft_check_bgstatus();
	g_retval = 130;
	g_input_mode = STD_INPUT;
	return (0);
}

int			keyboard_ctrl_c(union u_tc *term, char **buff, t_cursor *cursor)
{
	if (term->key == CTRL_C)
	{
		if (cursor->ctrl_r)
		{
			update_buff(buff, cursor);
			ft_strdel(&(cursor->prompt));
			cursor->prompt_len = mkprompt(&(cursor->prompt));
			cursor->start = ft_strlen(*buff);
			keyboard_ctrl_c_wiper(buff, cursor);
			return (0);
		}
		keyboard_ctrl_c_wiper(buff, cursor);
		return (0);
	}
	return (1);
}

int			keyboard_ctrl_d(union u_tc *term, char **buff, t_cursor *cursor)
{
	if (term->key == CTRL_D)
	{
		if (cursor->ctrl_r && cursor->match)
		{
			update_buff(buff, cursor);
			delete_key(buff, cursor);
			cursor->prompt_len = mkprompt(&(cursor->prompt));
			return (0);
		}
		if (*buff && **buff)
			delete_key(buff, cursor);
		else if (g_input_mode == STD_INPUT)
		{
			ft_putendl("exit");
			if (ft_clean_exit(NULL, g_retval))
				g_retval = 146;
		}
		keyboard_ctrl_c_wiper(buff, cursor);
		g_retval = 146;
		return (0);
	}
	return (1);
}

int			keyboard_ctrl_search(union u_tc *term, char **buff,
														t_cursor *cursor)
{
	if (term->key == CTRL_D)
	{
		if (!**buff)
			return (keyboard_ctrl_d(term, buff, cursor));
	}
	if (term->key == CTRL_C || term->key == CTRL_D)
	{
		update_buff(buff, cursor);
		ft_strdel(&(cursor->prompt));
		cursor->prompt_len = mkprompt(&(cursor->prompt));
		cursor->start = ft_strlen(*buff);
		keyboard_ctrl_c_wiper(buff, cursor);
		return (0);
	}
	return (1);
}
