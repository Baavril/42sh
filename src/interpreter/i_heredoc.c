/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:36:54 by bprunevi          #+#    #+#             */
/*   Updated: 2020/07/06 12:31:14 by tgouedar         ###   ########.fr       */
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
** The following funtcion is just a repeat from the above : it was previously
** being developped by a dev but the above was fixed for multiple compatibility
** reasons by another dev that did not know the >>- feature and deemed it non
** essential. (Note from latter hotfixing dev to former)
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
}
