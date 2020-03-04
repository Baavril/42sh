/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:25:22 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 14:57:24 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdio.h>
#include <stdint.h>

static int		display_select(char *str, t_cursor *cursor)
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

static int		display_all(char *str, t_cursor *cursor)
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

int				display(char *str, t_cursor *c)
{
	size_t			col;
	size_t			x;
	size_t			backup;
	static size_t	lines_offset = 0;

	x = 0;
	col = tgetnum("co");
	backup = c->end;
	if (c->end > c->start - (c->start % tgetnum("co"))
			+ tgetnum("co") * tgetnum("li") - c->prompt_len - 1)
		c->end = c->start - (c->start % tgetnum("co"))
			+ tgetnum("co") * tgetnum("li") - c->prompt_len - 1;
	if (tgetent(NULL, getenv("TERM")) != 1)
		return (1);
	if (c->end == c->start && c->end == 0)
		lines_offset = c->prompt_len / col;
	while (lines_offset--)
		ft_putstr(tgetstr("up", NULL));
	lines_offset = display_all(str, c);
	x = ((c->end + c->prompt_len) / col) - lines_offset;
	while (x--)
		ft_putstr(tgetstr("up", NULL));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (c->start + c->prompt_len) % col));
	c->end = backup;
	return (0);
}
