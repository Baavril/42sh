/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:36:54 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/11 14:48:08 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "parser.h"
#include "prompt.h"
#include <unistd.h>
#include "termcaps.h"
#include "expansions.h"

static void			get_heredoc_line(char **line)
{
	char		*buff;

	while (!**line || (*line)[ft_strlen(*line) - 1] != '\n')
	{
		if (isatty(STDIN_FILENO))
		{
			t_cursor	cursor;
			ft_init_cursor(&cursor);
			mkprompt_quote("\'", &(cursor.prompt), &(cursor.prompt_len));
			get_stdin(&cursor, &buff);
		}
		else
			get_next_line(STDIN_FILENO, &buff);
		buff = ft_strjoinfree(buff, ft_strdup("\n"));
		expansions_treatment(&buff, 1);
		*line = ft_strjoinfree(*line, buff);
		write(0, "\n", 1);
	}
}

void				process_heredoc(char **area)
{
	char		*name;
	char		*line;

	name = ft_strjoinfree(*area, ft_strdup("\n"));
	*area = ft_strdup("");
	line = ft_strdup("");
	set_termcaps(TC_INPUT);
	while (!line || (ft_strcmp(line, name)))
	{
		*area = ft_strjoinfree(*area, line);
		line = ft_strdup("");
		get_heredoc_line(&line);
	}
	ft_strdel(&name);
	ft_strdel(&line);
	set_termcaps(TC_RESTORE);
}

int					i_dless(t_elem left, t_elem right)
{
	int			pipe_fd[2];

	(void)left;
	pipe(pipe_fd);
	ft_putstr_fd(right.c, pipe_fd[1]);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (1);
	close(pipe_fd[1]);
	return (0);
}

int					i_dlessdash(t_elem left, t_elem right)
{
	int			pipe_fd[2];

	(void)left;
	pipe(pipe_fd);
	ft_putstr_fd(right.c, pipe_fd[1]);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (1);
	close(pipe_fd[1]);
	return (0);
}
