/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/26 23:19:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "libft.h"
#include "quote.h"
#include "input.h"
#include "prompt.h"
#include "display.h"
#include "history.h"
#include "termcaps.h"
#include "shell_variables.h"

#include <unistd.h>
#include <stdint.h>

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

static int				ft_agregate_line(t_cursor *cursor, char **buff)
{
	int			ret;
	char		*tmp;

	ret = 0;
	if ((cursor))
		get_stdin(cursor, &tmp);
	else if ((ret = get_next_line(STDIN_FILENO, &tmp)) < 0)
		return (1);
	if (!(*tmp) && !ret)
		return (1);
	*buff = ft_strjoinfree(*buff, ft_strdup("\n"));
	*buff = ft_strjoinfree(*buff, tmp);
	if ((cursor))
	{
		ft_strdel(&(cursor->prompt));
		write(1, "\n", 1);
		ft_init_cursor(cursor);
	}
	return (0);
}

static int				read_command(char **buff)
{
	int			ret;
	t_cursor	cursor;

	ft_init_cursor(&cursor);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	if (set_termcaps(TC_INPUT))
		return (2);
	cursor.prompt_len = mkprompt(&(cursor.prompt));
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
	return (SUCCESS);
}

int						get_input(char **input, int argc)
{
	int			ret;
	t_list		*unclosed_inhib;

	if (argc == 1)
		if ((ret = read_command(input)) != 1)
			return (ret);
	unclosed_inhib = NULL;
	if ((ret = get_next_line(STDIN_FILENO, input)) < 0)
		return (ret);
	if (!(**input) && !ret)
		return (1);
	while ((ret = quote_prompt(&unclosed_inhib, *input)) == ESC_NL
			|| (unclosed_inhib))
	{
		if (ft_agregate_line(NULL, input))
		{
			ret = ERR;
			break ;
		}
		ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
	}
	if (ret == ERR)
	{
		ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
//		psherror();
	}
	return ((ret == ERR || ret == ESC_NL) ? 1 : SUCCESS);
}
