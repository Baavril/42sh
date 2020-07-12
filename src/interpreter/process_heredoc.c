/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 12:33:23 by tgouedar          #+#    #+#             */
/*   Updated: 2020/07/12 23:42:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "expansions.h"
#include "termcaps.h"
#include "prompt.h"
#include "input.h"
#include "error.h"
#include "libft.h"
#include "quote.h"

extern int				g_input_mode;

static void				ft_catline_heredoc(char **input, char **last_line)
{
	if (!(*input))
		*input = *last_line;
	else
	{
		*input = ft_strnjoinfree(3, *input, ft_strdup("\n"), *last_line);
		*last_line = ft_strrchr(*input, '\n') + 1;
	}
	write(STDERR_FILENO, "\n", 1);
}

static int				read_heredoc(char **input, char *to_match)
{
	char		*last_line;
	t_cursor	cursor;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	if (!(g_input_mode = 1) && set_termcaps(TC_INPUT))
		return (2);
	last_line = "";
	*input = NULL;
	while (ft_strcmp(last_line, to_match))
	{
		ft_init_cursor(&cursor, 4);
		get_stdin(&cursor, &last_line);
		ft_strdel(&(cursor.prompt));
		if (!g_input_mode)
		{
			ft_strdel(&last_line);
			break ;
		}
		ft_catline_heredoc(input, &last_line);
	}
	ft_strdel(&to_match);
	set_termcaps(TC_RESTORE);
	return (0);
}

int						process_heredoc(char **input)
{
	char		*to_match;
	char		*tmp;
	int			ret;

	expansions_treatment(input, 1);
	to_match = *input;
	if ((ret = read_heredoc(input, to_match)) != 1)
		return (ret);
	if ((ret = get_next_line(STDIN_FILENO, &tmp)) < 0)
		return (ret);
	*input = ft_strdup("");
	while (ft_strcmp(to_match, tmp))
	{
		*input = ft_strnjoinfree(3, *input, tmp, ft_strdup("\n"));
		if ((ret = get_next_line(STDIN_FILENO, &tmp)) < 1 && !(*tmp))
			break ;
	}
	if (ft_strcmp(to_match, tmp))
		psherror(e_unexpected_eof, NULL, e_invalid_type);
	else
		ft_strdel(&tmp);
	ft_strdel(&to_match);
	return ((ret == ERR || ret == EOF_ERR || ret == ESC_NL) ? 1 : 0);
}
