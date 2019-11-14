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


static int display_select(char *str, size_t start, size_t end)
{
	size_t swap;
	if (start > end)
	{
		swap = start;
		start = end;
		end = swap;
	}
	write(1, str, start);
	ft_putstr(tgetstr("mr", NULL));
	write(1, &str[start], end - start);
	ft_putstr(tgetstr("me", NULL));
	ft_putstr(&str[end]);
	return(0);
}

static int display_all(char *str, size_t pos, size_t end, t_cursor cursor)
{
	size_t col;

	col = tgetnum("co");
	ft_putstr(tgetstr("cr", NULL));
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(cursor.prompt);
	if (end == SIZE_MAX || end > cursor.end)
		ft_putstr(str);
	else
		display_select(str, pos, end);
	if (!((cursor.end + cursor.prompt_len) % col))
		write(1, "\n", 1);
	return((pos + cursor.prompt_len) / col);
}

int display(char *str, size_t pos, size_t end, t_cursor cursor)
{
	size_t col;
	size_t x;
	static size_t lines_offset = 0;

	x = 0;
	if (tgetent(NULL, getenv("TERM")) != 1)
		return(1);
	col = tgetnum("co");
	// sets lines_offset value to normal if string is empty : ISSUE HERE
	if (cursor.end == pos && cursor.end == 0) // We enter this when opening a new, fresh prompt (usually after entering a command). This test is just not enough !
		lines_offset = cursor.prompt_len / col;

	//use the value of lines_offset
	while (lines_offset--)
		ft_putstr(tgetstr("up", NULL));

	//reset lines_offset value and display text
	lines_offset = display_all(str, pos, end, cursor);

	//Reposition cursor
	x = ((cursor.end + cursor.prompt_len) / col) - lines_offset;
	while (x--)
		ft_putstr(tgetstr("up", NULL));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (pos + cursor.prompt_len) % col));

	return(0);
}
