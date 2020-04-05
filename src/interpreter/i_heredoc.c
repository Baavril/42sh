/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:36:54 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/23 09:22:00 by petitfish        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "termcaps.h"
#include "parser.h"
#include "prompt.h"
#include <unistd.h>

static char	*find_firstchar(char *str)
{
	if (str)
		while (ft_isspace(*str))
			str++;
	return (str);
}

int			i_dless(t_elem left, t_elem right)
{
	t_cursor	cursor;
	char		*buff;
	int			pipe_fd[2];
	int			i;

	(void)left;
	set_termcaps(TC_INPUT);
	buff = NULL;
	pipe(pipe_fd);
	i = 0;
	while (!buff || (write(1, "\n", 1) && ft_strcmp(right.c, buff)))
	{
		while (i)
		{
			ft_putstr_fd("\n", pipe_fd[1]);
			i--;
		}
		ft_putstr_fd(buff, pipe_fd[1]);
		ft_strdel(&buff);
		ft_init_cursor(&cursor);
		cursor.prompt_len = mkprompt_quote("\'", &(cursor.prompt));
		get_stdin(&cursor, &buff);
		i++;
	}
	close(pipe_fd[1]);
	set_termcaps(TC_RESTORE);
	return (dup2(pipe_fd[0], 0));
}

int			i_dlessdash(t_elem left, t_elem right)
{
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
		cursor.prompt_len = mkprompt_quote("", &(cursor.prompt));
		get_stdin(&cursor, &buff);
		ft_putstr_fd("\n", pipe_fd[1]);
	}
	close(pipe_fd[1]);
	set_termcaps(TC_RESTORE);
	return (dup2(pipe_fd[0], 0));
}
