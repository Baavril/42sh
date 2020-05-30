/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/30 18:16:08 by tgouedar         ###   ########.fr       */
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

extern struct s_svar	*g_svar;

void					ft_init_cursor(t_cursor *cursor, int prompt_mode)
{
	cursor->match = NULL;
	cursor->in = SIZE_MAX;
	cursor->start = 0;
	cursor->end = 0;
	cursor->match_ret = 0;
	if (prompt_mode == 1)
		cursor->prompt_len = mk_prompt(&(cursor->prompt), PS1);
	else if (prompt_mode == 2)
		cursor->prompt_len = mk_prompt(&(cursor->prompt), PS2);
	else if (prompt_mode == 3)
		cursor->prompt_len = mk_prompt(&(cursor->prompt), PS3);
	else if (prompt_mode == 4)
		cursor->prompt_len = mk_prompt(&(cursor->prompt), PS4);
	else
	{
		cursor->prompt_len = 0;
		cursor->prompt = NULL;
	}
	cursor->ctrl_r = 0;
	cursor->on = 0;
}

static void				ft_syntaxerr(t_list *unclosed_inhib)
{
	char	err_mess[2];

	err_mess[0] = *((char*)(unclosed_inhib->content));
	err_mess[1] = '\0';
	psherror(e_syntax_error, err_mess, e_parsing_type);
}

static int				ft_agregate_line(t_cursor *cursor, char **buff)
{
	int			ret;
	char		*tmp;

	ret = 0;
	if ((cursor))
	{
		ft_init_cursor(cursor, 2);
		get_stdin(cursor, &tmp);
	}
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
	}
	return (NO_ERR);
}

static int				read_command(char **buff)
{
	int			ret;
	t_cursor	cursor;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	if (set_termcaps(TC_INPUT))
		return (2);
	ft_init_cursor(&cursor, 1);
	get_stdin(&cursor, buff);
	write(1, "\n", 1);
	ft_strdel(&(cursor.prompt));
	while (**buff
	&& (ret = ft_check_inhib(*buff)) == 1)
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
	while ((ret = quote_check(&unclosed_inhib, *input)) == ESC_NL
			|| (ret != ERR && unclosed_inhib))
	{
		if ((ret = ft_agregate_line(NULL, input)) != NO_ERR)
			break ;
		ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
	}
	if (ret == EOF_ERR)
		psherror(e_unexpected_eof, NULL, e_invalid_type);
	if (ret == ERR && unclosed_inhib)
		ft_syntaxerr(unclosed_inhib);
	ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
	return ((ret == ERR || ret == EOF_ERR || ret == ESC_NL) ? 1 : SUCCESS);
}
