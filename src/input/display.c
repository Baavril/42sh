/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:25:22 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/13 13:32:01 by baavril          ###   ########.fr       */
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
	return(0);
}

static int display_all(char *str, t_cursor *cursor)
{
	size_t col;

	col = tgetnum("co");
	ft_putstr(tgetstr("cr", NULL));
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(cursor->prompt);
	if (cursor->in == SIZE_MAX || cursor->in > cursor->end)
		ft_putstr(str);
	else
		display_select(str, cursor);
	if (!((cursor->end + cursor->prompt_len) % col))
		write(1, "\n", 1);
	return((cursor->start + cursor->prompt_len) / col);
}

int display(char *str, t_cursor *cursor)
{
	size_t col;
	size_t x;
	static size_t lines_offset = 0;

	x = 0;
	col = tgetnum("co");
	if (tgetent(NULL, getenv("TERM")) != 1)
		return(1);
	// sets lines_offset value to normal if string is empty : ISSUE HERE
	if (cursor->end == cursor->start && cursor->end == 0) // We enter this when opening a new, fresh prompt (usually after entering a command). This test is just not enough !
		lines_offset = cursor->prompt_len / col;

	//use the value of lines_offset
	while (lines_offset--)
		ft_putstr(tgetstr("up", NULL));

	//reset lines_offset value and display text
	lines_offset = display_all(str, cursor);

	//Reposition cursor
	x = ((cursor->end + cursor->prompt_len) / col) - lines_offset;
	while (x--)
		ft_putstr(tgetstr("up", NULL));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (cursor->start + cursor->prompt_len) % col));

	return(0);
}
