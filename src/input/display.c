/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:25:22 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/15 14:58:01 by yberramd         ###   ########.fr       */
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
	if (cursor->start < cursor->in)
	{
		write(0, str, cursor->start);
		ft_putstr_fd(tgetstr("mr", NULL), 0);
		write(0, &str[cursor->start], cursor->in - cursor->start);
		ft_putstr_fd(tgetstr("me", NULL), 0);
		ft_putstr_fd(&str[cursor->in], 0);
	}
	else
	{
		write(0, str, cursor->in);
		ft_putstr_fd(tgetstr("mr", NULL), 0);
		write(0, &str[cursor->in], cursor->start - cursor->in);
		ft_putstr_fd(tgetstr("me", NULL), 0);
		ft_putstr_fd(&str[cursor->start], 0);
	}
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
	ft_putstr_fd(tgetstr("cr", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(cursor->prompt, 0);
	if (cursor->in == SIZE_MAX || cursor->in > cursor->end)
		ft_putnstr_fd(str, cursor->end, 0);
	else if (str)
		display_select(str, cursor);
	if (!((cursor->end + cursor->prompt_len) % col) && cursor->prompt_len)
		write(0, "\n", 1);
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
	ft_putstr_fd(tgoto(tgetstr("ch", NULL), 0, rtn % col), 0);
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
		ft_putstr_fd(tgetstr("up", NULL), 0);
	lines_offset = display_all(str, c);
	x = get_lines_offset(str, col, c->prompt_len, c->end) - lines_offset;
	while (x-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	place_cursor(str, col, c->prompt_len, c->start);
	c->end = backup;
	return (0);
}
