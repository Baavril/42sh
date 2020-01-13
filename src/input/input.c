/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/03 17:33:00 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "termcaps.h"
#include "keys.h"
#include "prompt.h"
#include "display.h"
#include "history.h"

#include <unistd.h>
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

int read_command(char **buff)
{
	char		*tmp;
	t_cursor	cursor;

	ft_init_cursor(&cursor);
	if (!isatty(STDIN_FILENO))
		return (1);
	if (set_termcaps(TC_INPUT))
		return (2);
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
	set_termcaps(TC_RESTORE);
	return (0);
}
