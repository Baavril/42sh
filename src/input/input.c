/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/09 17:37:59 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "keys.h"
#include "prompt.h"
#include "display.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdint.h>

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
	term.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
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

int get_stdin(t_cursor cursor, char **buff)
{
	char c;

	inside_history = NULL;
	*buff = ft_strdup("");
	display(*buff, cursor.end, SIZE_MAX, cursor);
	while (1)
	{
		if (read(0, &c, 1) == -1)
			return(-1);
		if (ft_isprint(c))
			normal_char(buff, &cursor, c);
		else if (c == '\177')
			backspace_key(buff, &cursor);
		else if (c == '\t')
			tab_key(buff, &cursor);
		else if (c == '\033')
			escape_char(buff, &cursor);
		else if (c == '\n')
		{
			display(*buff, cursor.start, SIZE_MAX, cursor);
			ft_strdel(&inside_history);
			return(0);
		}
		display(*buff, cursor.end, cursor.in, cursor);
	}
	return(1);
}

void	ft_init_cursor(t_cursor *cursor)
{
	cursor->prompt = NULL;
	cursor->in = SIZE_MAX;
	cursor->end = 0;
	cursor->start = 0;
	cursor->prompt_len = 0;
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
	get_stdin(cursor, buff);
	write(1, "\n", 1);
	while (**buff && (cursor.prompt_len = mkprompt_quote(*buff, &(cursor.prompt))))
	{
		get_stdin(cursor, &tmp);
		*buff = ft_strjoinfree(*buff, tmp);
		ft_strdel(&(cursor.prompt));
		write(1, "\n", 1);
	}
	ft_strdel(&(cursor.prompt));
	toggle_termcaps();
	return(0);
}
