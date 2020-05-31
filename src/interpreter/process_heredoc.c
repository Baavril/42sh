/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 12:33:23 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/31 16:17:32 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "termcaps.h"
#include "prompt.h"
#include "input.h"
#include "error.h"
#include "libft.h"
#include "quote.h"

extern int				g_input_mode;

static int				read_heredoc(char **input, char *to_match)
{
	char		*last_line;
	t_cursor	cursor;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	if (!(g_input_mode = 0) && set_termcaps(TC_INPUT))
		return (2);
	g_input_mode = 1;
	ft_init_cursor(&cursor, 4);
	get_stdin(&cursor, input);
	last_line = *input;
	ft_strdel(&(cursor.prompt));
	write(1, "\n", 1);
	while (last_line && ft_strcmp(last_line, to_match))
	{
		ft_init_cursor(&cursor, 4);
		get_stdin(&cursor, &last_line);
		if (!g_input_mode)
		{
			ft_strdel(&last_line);
			break ;
}
		*input = ft_strnjoinfree(3, *input, ft_strdup("\n"), last_line);
		last_line = ft_strrchr(*input, '\n') + 1;
		ft_strdel(&(cursor.prompt));
		write(1, "\n", 1);
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
