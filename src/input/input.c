/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/27 16:40:36 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "libft.h"
#include "quote.h"
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

static int				ft_agregate_line(t_cursor *cursor, char **buff)
{
	int			ret;
	char		*tmp;

	ret = 0;
	if ((cursor))
		get_stdin(cursor, &tmp);
	else if ((ret = get_next_line(STDIN_FILENO, &tmp)) < 0)
		return (ERR);
	if (!(*tmp) && !ret)
	{
		ft_strdel(&tmp);
		return (EOF_ERR);
	}
	*buff = ft_strjoinfree(*buff, ft_strdup("\n"));
	*buff = ft_strjoinfree(*buff, tmp);
	if ((cursor))
	{
		ft_strdel(&(cursor->prompt));
		write(1, "\n", 1);
		ft_init_cursor(cursor);
	}
	return (NO_ERR);
}

static int				read_command(char **buff)
{
	int			ret;
	t_cursor	cursor;

	ret = 0;
	ft_init_cursor(&cursor);
	if ((g_input_mode = STD_INPUT) && !isatty(STDIN_FILENO))
		return (1);
	if (set_termcaps(TC_INPUT))
		return (2);
	cursor.prompt_len = mkprompt(&(cursor.prompt));
	get_stdin(&cursor, buff);
	write(0, "\n", 1);
	ft_strdel(&(cursor.prompt));
	ft_init_cursor(&cursor);
	while (**buff && (ret = mkprompt_quote(*buff,
							&(cursor.prompt), &(cursor.prompt_len))) == 1)
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

	if (argc == 1 && (ret = read_command(input)) != 1)
		return (ret);
	unclosed_inhib = NULL;
	if ((ret = get_next_line(STDIN_FILENO, input)) < 0)
		return (ret);
	if (!(**input) && !ret)
		return (1);
	while ((ret = quote_prompt(&unclosed_inhib, *input)) == ESC_NL
			|| (ret != ERR && unclosed_inhib))
	{
		if ((ret = ft_agregate_line(NULL, input)) != NO_ERR)
			break ;
		ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
	}
	if (ret == EOF_ERR)
		psherror(e_unexpected_eof, NULL, e_invalid_type);
	if (ret == ERR && unclosed_inhib)
		psherror(e_syntax_error, unclosed_inhib->content, e_parsing_type);
	ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
	return ((ret == ERR || ret == EOF_ERR || ret == ESC_NL) ? 1 : SUCCESS);
}
