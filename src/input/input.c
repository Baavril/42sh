/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/19 10:07:30 by baavril          ###   ########.fr       */
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

void	update_buff(char **buff, t_cursor *cursor)
{
	size_t len;

	len = 0;
	ft_bzero(*buff, ft_strlen(*buff));
	if (cursor->match)
	{
		len = ft_strlen(cursor->match);
		if (cursor->end < len)
			*buff = buff_realloc(*buff, len);
		ft_strcpy(*buff, cursor->match);
	}
	cursor->end = len;
}

int toggle_termcaps(void)
{
	struct termios term;

	term.c_cc[VMIN] = 1; /* si VTIME = 0 et ICANON desactive VMIN determine le nombre d'octets lus par read */
	term.c_cc[VTIME] = 0;
	if (tcgetattr(STDIN_FILENO, &term) < 0)
	{
		printf("Error tcgetattr");
		return(1);
	}
	term.c_lflag ^= (ECHO | ICANON | ISIG | IEXTEN);
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0)
	{
		printf("Error tcsetattr");
		return(1);
	}
	if (tgetent(NULL, getenv("TERM")) != 1)
	{
		printf("Error tgetent");
		return(1);
	}
	return(0);
}

int	set_reader(char **buff, t_cursor *cursor)
{
	if (cursor->ctrl_r)
	{
		ft_strdel(&(cursor->prompt));
		cursor->prompt_len = search_prompt(cursor, *buff);
		cursor->end = ft_strlen(cursor->match);
		display(cursor->match, cursor);
		cursor->end = ft_strlen(*buff);
		return (0);
	}
	display(*buff, cursor);
	return (1);
}

int		standard_analyzer(union u_tc term, char **buff, t_cursor *cursor)
{
	keyboard_normal_char(term, buff, cursor);
	keyboard_backspace(term, buff, cursor);
	keyboard_tabulation(term, buff, cursor);
	keyboard_ctrl_l(term);
	if (keyboard_dispatcher(term, buff, cursor) == 0
	|| !keyboard_enter(term, buff, cursor))
		return(0);
	set_reader(buff, cursor);
	return (1);
}


int	search_history(union u_tc term, char **buff, t_cursor *cursor)
{
	if (!cursor->ctrl_r)
	{
		ft_strdel(&(cursor->prompt));
		ft_init_cursor(cursor);
		cursor->ctrl_r = 1;
	}
	keyboard_normal_char(term, buff, cursor);
	keyboard_backspace(term, buff, cursor);
	if (!(keyboard_enter(term, buff, cursor)))
		return (0);
	else if (keyboard_tabulation(term, buff, cursor) == 0
	|| keyboard_dispatcher(term, buff, cursor) >= 0)
	{
		cursor->ctrl_r = 0;
		ft_strdel(&(cursor->prompt));
		cursor->prompt_len = mkprompt(&(cursor->prompt));
		cursor->on = 0;
		return (1);
	}
	cursor->on = 1;
	set_reader(buff, cursor);
	return (-1);
}

int	get_stdin(t_cursor *cursor, char **buff)
{
	union	u_tc termcaps;
	int flag;

	flag = 0;
	if (ft_init_tab() == 1)
		return (1);
	inside_history = NULL;
	*buff = ft_strdup("");
	set_reader(buff, cursor);
	while (read(STDIN_FILENO, termcaps.buff, COUNT_KEY))
	{
		if (!(ft_strcmp(&termcaps.buff[2], CTRL_R)) || cursor->on == 1)
		{
			if ((flag = search_history(termcaps, buff, cursor)) == 0)
			{
				ft_strdel(&(cursor->prompt));
				return (0);
			}
		}
		if (!cursor->on)
		{
			if (!(standard_analyzer(termcaps, buff, cursor)))
			{
				ft_strdel(&inside_history);
				ft_strdel(&cursor->prompt);
				return(0);
			}
		}
	}
	return(1);
}

void	ft_init_cursor(t_cursor *cursor)
{
	cursor->prompt = NULL;
	cursor->match = NULL;
	cursor->in = SIZE_MAX;
	cursor->start = 0;
	cursor->end = 0;
	cursor->match_ret = 0;
	cursor->prompt_len = 0;
	cursor->ctrl_r = 0;
	cursor->on = 0;
}

int read_command(char **buff)
{
	char *tmp;
	t_cursor cursor;

	ft_init_cursor(&cursor);
	if (!isatty(STDIN_FILENO))
		return(1);
	if (toggle_termcaps())
		return(2);
	cursor.prompt_len = mkprompt(&(cursor.prompt));
	get_stdin(&cursor, buff);
	write(1, "\n", 1);
	ft_init_cursor(&cursor);
	while (**buff && (cursor.prompt_len = mkprompt_quote(*buff, &(cursor.prompt))))
	{
		get_stdin(&cursor, &tmp);
		*buff = ft_strjoinfree(*buff, tmp);
		ft_strdel(&(cursor.prompt));
		write(1, "\n", 1);
		ft_init_cursor(&cursor);
	}
	ft_strdel(&(cursor.prompt));
	toggle_termcaps();
	return(0);
}
