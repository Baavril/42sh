/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/02 20:46:03 by tgouedar         ###   ########.fr       */
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

//int toggle_termcaps(void)
//{
//	struct termios	term;
//
//	term.c_cc[VMIN] = 1; /* si VTIME = 0 et ICANON desactive VMIN determine le nombre d'octets lus par read */
//	term.c_cc[VTIME] = 0;
//	if (tcgetattr(STDIN_FILENO, &term) < 0)
//	{
//		printf("Error tcgetattr");
//		return (1);
//	}
//	term.c_lflag ^= (ECHO | ICANON | ISIG | IEXTEN);
//	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0)
//	{
//		printf("Error tcsetattr");
//		return (1);
//	}
//	if (tgetent(NULL, getenv("TERM")) != 1)
//	{
//		printf("Error tgetent");
//		return (1);
//	}
//	return (0);
//}

void	toggle_sig_mode(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag ^= ISIG;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}
int read_command(char **buff)
{
	char		*tmp;
	t_cursor	cursor;

	ft_init_cursor(&cursor);
	if (!isatty(STDIN_FILENO))
		return (1);
//	if (toggle_termcaps())
//		return (2);
	toggle_sig_mode();
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
	toggle_sig_mode();
	return (0);
}
