/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_commands_ctrl.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:13:16 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/16 23:05:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "jcont.h"
#include "error.h"
#include "prompt.h"

#include <term.h>
#include <curses.h>

extern int	g_retval;

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
	char	*tmp;
	int		tmp_len;

	tmp = NULL;
	tmp_len = 0;
	ft_strdel(buff);
	*buff = ft_strdup("");
	tmp = cursor->prompt;
	tmp_len = cursor->prompt_len;
	ft_init_cursor(cursor);
	cursor->prompt = tmp;
	cursor->prompt_len = tmp_len;
	ft_putchar('\n');
	ft_check_bgstatus();
	g_retval = 130;
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
		else if (ft_clean_exit(NULL, g_retval))
			g_retval = 146;
	}
	return (1);
}
