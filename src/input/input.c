/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/08 18:04:26 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "termcaps.h"
#include "keys.h"
#include "prompt.h"
#include "display.h"
#include "history.h"
#include "shell_variables.h"

#include <unistd.h>
#include <stdint.h>

extern struct s_svar	*g_svar;

void				ft_init_cursor(t_cursor *cursor)
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

int					ft_strplen(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\033')
		{
			while (str[i] != 'm')
				++i;
			++i;
		}
		if (ft_isprint(str[i]))
			++j;
		++i;
	}
	return (j);
}

int					init_prompt(t_cursor *cursor)
{
	struct s_svar	*voyager;

	update_prompt_var();
	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PS1)))
		{
			cursor->prompt_len = ft_strplen(voyager->value);
			cursor->prompt = ft_strdup(voyager->value);
			return (0);
		}
		voyager = voyager->next;
	}
	cursor->prompt_len = 0;
	return (0);
}

static void				ft_agregate_line(t_cursor *cursor, char **buff)
{
	char		*tmp;

	get_stdin(cursor, &tmp);
	*buff = ft_strjoinfree(*buff, ft_strdup("\n"));
	*buff = ft_strjoinfree(*buff, tmp);
	ft_strdel(&(cursor->prompt));
	write(1, "\n", 1);
	ft_init_cursor(cursor);
	
}

int					read_command(char **buff)
{
	int			ret;
	t_cursor	cursor;

	ft_init_cursor(&cursor);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	if (set_termcaps(TC_INPUT))
		return (2);
	init_prompt(&cursor);
	get_stdin(&cursor, buff);
	write(1, "\n", 1);
	ft_strdel(&(cursor.prompt));
	ft_init_cursor(&cursor);
	while (**buff
	&& (ret = mkprompt_quote(*buff, &(cursor.prompt), &(cursor.prompt_len))) == 1)
		ft_agregate_line(&cursor, buff);
	if (ret == -1)
	{
		history(ADD_CMD, buff, NULL);
		free(*buff);
		*buff = ft_strdup("");
	}
	set_termcaps(TC_RESTORE);
	return (0);
}
