/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:12:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/18 20:57:52 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "keys.h"
#include "prompt.h"
#include "display.h"
#include "history.h"

#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdint.h>

t_dispatch_keys		g_dispatch_keys[] =
{
	{NULL, &left_arrow},
	{NULL, &right_arrow},
	{NULL, &up_arrow},
	{NULL, &down_arrow},
	{NULL, &delete_key},
	{NULL, &home_key},
	{NULL, &next_word},
	{NULL, &previous_word},
	{NULL, &end_key},
	{NULL, &select_key},
	{NULL, &paste_key},
	{NULL, NULL}
};

int	ft_init_tab(void)
{
	if (!(g_dispatch_keys[0].key_path = tgetstr("kl", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[1].key_path = tgetstr("kr", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[2].key_path = tgetstr("ku", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[3].key_path = tgetstr("kd", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[4].key_path = tgetstr("kD", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[5].key_path = tgetstr("kh", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[6].key_path = tgetstr("kN", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[7].key_path = tgetstr("kP", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[8].key_path = "F\0"))
		return (1);
	if (!(g_dispatch_keys[9].key_path = "1;2A"))
		return (1);
	if (!(g_dispatch_keys[10].key_path = "1;2B"))
		return (1);
	return (0);
}

int keyboard_normal_char(union u_tc term, char **buff, t_cursor *cursor)
{
	if (ft_isprint(term.key))
	{
		if (cursor->ctrl_r)
		{
			cursor->start = ft_strlen(*buff);
			normal_char(buff, cursor, term.key);
			cursor->match = get_history(buff, cursor);
			return (0);
		}
		normal_char(buff, cursor, term.key);
		return (0);
	}
	return (1);
}

int keyboard_tabulation(union u_tc term, char **buff, t_cursor *cursor)
{
	if (term.key == TABULATION)
	{
		if (cursor->ctrl_r)
		{
			tab_key(buff, cursor);
			ft_strdel(&(cursor->prompt));
			cursor->prompt_len = mkprompt(&(cursor->prompt));
			history(RESET, buff, NULL);
			return (0);
		}
		tab_key(buff, cursor);
		return (0);
	}
	return (1);
}

int keyboard_enter(union u_tc term, char **buff, t_cursor *cursor)
{
	if (term.key == ENTER)
	{
		if (cursor->ctrl_r)
		{
			update_buff(buff, cursor);
			history(RESET, buff, NULL);
			return (0);
		}
		return (0);
	}
	return (1);
}

int keyboard_backspace(union u_tc term, char **buff, t_cursor *cursor)
{
	if (term.key == BACKSPACE)
	{
		if (cursor->ctrl_r)
		{
			cursor->start = ft_strlen(*buff);
			backspace_key(buff, cursor);
			cursor->match = get_history(buff, cursor);
			return (0);
		}
		backspace_key(buff, cursor);
		return (0);
	}
	return (1);
}

int keyboard_ctrl_l(union u_tc term)
{
	if (term.key_c == CTRL_L)
	{
		ft_putstr(tgetstr("ho", NULL));
		return (0);
	}
	return (1);
}

int	keyboard_dispatcher(union u_tc term, char **buff, t_cursor *cursor)
{
	int i;

	i = 0;
	if (term.key == '\033')
	{
		i = 0;
		while (g_dispatch_keys[i].key_path != NULL)
		{
			if (ft_strncmp(g_dispatch_keys[i].key_path
			, &term.buff[2], ft_strlen(g_dispatch_keys[i].key_path)) == 0)
			{
				if (cursor->ctrl_r)
				{
					update_buff(buff, cursor);
					ft_strdel(&(cursor->prompt));
					cursor->prompt_len = mkprompt(&(cursor->prompt));
					history(RESET, buff, NULL);
				}
				if (((g_dispatch_keys[i].function_call)(buff, cursor)) == 0)
					return (0);
				return (1);
			}
			i++;
		}
	}
	return (-1);
}
