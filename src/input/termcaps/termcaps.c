/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:49:15 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/01 11:16:30 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "termcaps.h"
#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>

static struct termios	input_termcaps(struct termios term)
{
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_lflag = ECHOE;
	return (term);
}

int						set_termcaps(int arg)
{
	static struct termios	backup_term;
	struct termios			term;
	char					*tmp;

	if (tcgetattr(STDIN_FILENO, &term) < 0)
		return (1);
	if (arg == TC_SAVE)
		backup_term = term;
	if (arg == TC_RESTORE)
		term = backup_term;
	if (arg == TC_INPUT)
	{
		term = input_termcaps(term);
		tmp = ft_getenv("TERM");
		if (tgetent(NULL, tmp) != 1)
		{
			ft_strdel(&tmp);
			return (1);
		}
		ft_strdel(&tmp);
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		return (1);
	return (0);
}
