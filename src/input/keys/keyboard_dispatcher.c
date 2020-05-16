/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:42:22 by bprunev           #+#    #+#             */
/*   Updated: 2020/05/11 14:47:15 by tgouedar         ###   ########.fr       */
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

static char		*g_keylist[] = {
	"kl",
	"kr",
	"ku",
	"kd",
	"kD",
	"kh",
	"kN",
	"kP",
	NULL,
	"F\0",
	"1;2A",
	"1;2B",
	NULL
};

int		init_key_tab(void)
{
	int		i;
	char	*buff;

	i = 0;
	buff = NULL;
	while (g_keylist[i])
	{
		if ((buff = tgetstr(g_keylist[i], NULL)))
			g_dispatch_keys[i].key_path = buff + 2;
		else
			g_dispatch_keys[i].key_path = NULL;
		i++;
	}
	++i;
	while (g_keylist[i])
	{
		g_dispatch_keys[i - 1].key_path = g_keylist[i];
		i++;
	}
	return (0);
}

int		keyboard_dispatcher(union u_tc *term, char **buff, t_cursor *cursor)
{
	int i;

	if (term->key == ESC)
	{
		i = 0;
		while (g_dispatch_keys[i].key_path != NULL)
		{
			if (ft_strncmp(g_dispatch_keys[i].key_path, &term->buff[2],
								ft_strlen(g_dispatch_keys[i].key_path)) == 0)
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
