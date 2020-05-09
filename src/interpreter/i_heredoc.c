/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:36:54 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/09 17:59:19 by user42           ###   ########.fr       */
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

/*
**is the same as above, awaiting fix
*/

int			i_dlessdash(t_elem left, t_elem right)
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
	return (0);
}
