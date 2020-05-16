/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:36:54 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/16 20:47:31 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "termcaps.h"
#include "parser.h"
#include "prompt.h"
#include <unistd.h>

int			i_dless(t_elem left, t_elem right)
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

int			i_dlessdash(t_elem left, t_elem right)
{
	/*
	t_cursor	cursor;
	char		*buff;
	int			pipe_fd[2];

	(void)left;
	set_termcaps(TC_INPUT);
	buff = NULL;
	pipe(pipe_fd);
	while (!buff || (write(1, "\n", 1) && ft_strcmp(right.c, buff)))
	{
		ft_putstr_fd(find_firstchar(buff), pipe_fd[1]);
		ft_strdel(&buff);
		ft_init_cursor(&cursor);
		mkprompt_quote("", &(cursor.prompt), &(cursor.prompt_len));
		get_stdin(&cursor, &buff);
		ft_putstr_fd("\n", pipe_fd[1]);
	}
	close(pipe_fd[1]);
	set_termcaps(TC_RESTORE);
	*/
	(void)left;
	ft_printf("(%s)\n", right.c);
	return (0);
}
