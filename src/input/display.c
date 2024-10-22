/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:25:22 by bprunevi          #+#    #+#             */
/*   Updated: 2020/06/01 15:33:24 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "termcaps.h"

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
	write(STDERR_FILENO, str, cursor->start);
	ft_putstr_fd(tgetstr("mr", NULL), STDERR_FILENO);
	write(STDERR_FILENO, &str[cursor->start], cursor->in - cursor->start);
	ft_putstr_fd(tgetstr("me", NULL), STDERR_FILENO);
	ft_putstr_fd(&str[cursor->in], STDERR_FILENO);
	return (0);
}

int				get_lines_offset(char *str, int col, int prompt_len, int len)
{
	int rtn;
	int chr;

	rtn = 0;
	chr = prompt_len;
	while (len--)
	{
		chr++;
		if (*(str++) == '\n')
		{
			rtn += 1 + chr / col;
			chr = 0;
		}
	}
	rtn += chr / col;
	return (rtn);
}

static int		display_all(char *str, t_cursor *cursor)
{
	size_t col;

	col = tgetnum("co");
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("cd", NULL), STDERR_FILENO);
	ft_putstr_fd(cursor->prompt, STDERR_FILENO);
	if (cursor->in == SIZE_MAX || cursor->in > cursor->end)
		ft_putnstr_fd(str, cursor->end, STDERR_FILENO);
	else if (str)
		display_select(str, cursor);
	if (!((cursor->end + cursor->prompt_len) % col) && cursor->prompt_len)
		write(STDERR_FILENO, "\n", 1);
	return (get_lines_offset(str, col, cursor->prompt_len, cursor->start));
}

static void		place_cursor(char *str, int col, int prompt_len, int start)
{
	int	rtn;

	rtn = 0;
	while (start && str && *(str + --start) != '\n')
		rtn++;
	if (!start)
		rtn += prompt_len;
	ft_putstr_fd(tgoto(tgetstr("ch", NULL), 0, rtn % col), STDERR_FILENO);
}

int				display(char *str, t_cursor *c)
{
	int			col;
	int			x;
	int			backup;
	static int	lines_offset = 0;

	set_termcaps(TC_INPUT);
	x = 0;
	col = tgetnum("co");
	backup = c->end;
	if (c->end > c->start - (c->start % col)
			+ col * tgetnum("li") - c->prompt_len - 1)
		c->end = c->start - (c->start % col)
			+ col * tgetnum("li") - c->prompt_len - 1;
	if (!str)
		lines_offset = c->prompt_len / col;
	while (lines_offset-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), STDERR_FILENO);
	lines_offset = display_all(str, c);
	x = get_lines_offset(str, col, c->prompt_len, c->end) - lines_offset;
	while (x-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), STDERR_FILENO);
	place_cursor(str, col, c->prompt_len, c->start);
	c->end = backup;
	return (0);
}
