/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:25:22 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/26 15:37:43 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdio.h>
#include <stdint.h>


static int display_select(char *str, t_cursor *cursor)
{
	size_t swap;

	if (cursor->start > cursor->in)
	{
		swap = cursor->start;
		cursor->start = cursor->in;
		cursor->in = swap;
	}
	write(1, str, cursor->start);
	ft_putstr(tgetstr("mr", NULL));
	write(1, &str[cursor->start], cursor->in - cursor->start);
	ft_putstr(tgetstr("me", NULL));
	ft_putstr(&str[cursor->in]);
	return (0);
}

static int display_all(char *str, t_cursor *cursor)
{
	size_t col;

	col = tgetnum("co");
	ft_putstr(tgetstr("cr", NULL));
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(cursor->prompt);
	if (cursor->in == SIZE_MAX || cursor->in > cursor->end)
		ft_putnstr(str, cursor->end);
	else
		display_select(str, cursor);
	if (!((cursor->end + cursor->prompt_len) % col) && cursor->prompt_len)
		write(1, "\n", 1);
	return ((cursor->start + cursor->prompt_len) / col);
}

int display(char *str, t_cursor *cursor)
{
	size_t col;
	size_t x;
	static size_t lines_offset;
	size_t backup;

	x = 0;
	lines_offset = 0;
	col = tgetnum("co");
	backup = cursor->end;
	if (cursor->end > cursor->start - (cursor->start % tgetnum("co")) + tgetnum("co") * tgetnum("li") - cursor->prompt_len - 1)
		cursor->end = cursor->start - (cursor->start % tgetnum("co")) + tgetnum("co") * tgetnum("li") - cursor->prompt_len - 1;
	if (tgetent(NULL, getenv("TERM")) != 1)
		return (1);
	if (cursor->end == cursor->start && cursor->end == 0)
		lines_offset = cursor->prompt_len / col;
	while (lines_offset--)
		ft_putstr(tgetstr("up", NULL));
	lines_offset = display_all(str, cursor);
	x = ((cursor->end + cursor->prompt_len) / col) - lines_offset;
	while (x--)
		ft_putstr(tgetstr("up", NULL));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (cursor->start + cursor->prompt_len) % col));
	cursor->end = backup;
	return (0);
}
