/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/22 16:33:22 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "libft.h"
#include "input.h"
#include "error.h"
#include "prompt.h"
#include "display.h"
#include "history.h"
#include "termcaps.h"
#include "shell_variables.h"

#include <unistd.h>
#include <stdint.h>

int						g_input_mode = 0;
extern int				g_retval;
extern struct s_svar	*g_svar;

void					ft_init_cursor(t_cursor *cursor)
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

int						ft_strplen(char *str)
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

static void				ft_agregate_line(t_cursor *cursor, char **buff)
{
	char		*tmp;

	g_input_mode = QUOTE_INPUT;
	get_stdin(cursor, &tmp);
	if (g_input_mode == STD_INPUT)
	{
		if (g_retval == 146)
			psherror(e_eof_reached, "", e_invalid_type);
		ft_strdel(buff);
		ft_strdel(&tmp);
		*buff = ft_strdup("");
		return ;
	}
	*buff = ft_strjoinfree(*buff, ft_strdup("\n"));
	*buff = ft_strjoinfree(*buff, tmp);
	ft_strdel(&(cursor->prompt));
	write(0, "\n", 1);
	ft_init_cursor(cursor);
}

int						read_command(char **buff)
{
	int			ret;
	t_cursor	cursor;

	ft_init_cursor(&cursor);
	if (!isatty(STDIN_FILENO))
		return (1);
	if (set_termcaps(TC_INPUT))
		return (2);
	cursor.prompt_len = mkprompt(&(cursor.prompt));
	g_input_mode = STD_INPUT;
	get_stdin(&cursor, buff);
	write(0, "\n", 1);
	ft_strdel(&(cursor.prompt));
	ft_init_cursor(&cursor);
	while (**buff
	&& (ret = mkprompt_quote(*buff, &(cursor.prompt),
										&(cursor.prompt_len))) == 1)
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
