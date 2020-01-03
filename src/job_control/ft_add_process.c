/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 15:51:32 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/02 19:42:34 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "sig_handler.h"
#include "jcont.h"
#include "parser.h"

extern t_job	g_curjob;

void			ft_save_term_fd(int std_redir[3], int save_fd[3])
{
	if (std_redir[0] != STDIN_FILENO)
		save_fd[0] = dup(STDIN_FILENO);
	else
		save_fd[0] = STDIN_FILENO;
	if (std_redir[1] != STDOUT_FILENO)
		save_fd[1] = dup(STDOUT_FILENO);
	else
		save_fd[1] = STDOUT_FILENO;
	if (std_redir[2] != STDERR_FILENO)
		save_fd[2] = dup(STDERR_FILENO);
	else
		save_fd[2] = STDERR_FILENO;
}

void			ft_stdredir(int std_fd[3])
{
	if (std_fd[0] != STDIN_FILENO)
	{
		dup2(std_fd[0], STDIN_FILENO);
		close(std_fd[0]);
	}
	if (std_fd[1] != STDOUT_FILENO)
	{
		dup2(std_fd[1], STDOUT_FILENO);
		close(std_fd[1]);
	}
	if (std_fd[2] != STDERR_FILENO)
	{
		dup2(std_fd[2], STDERR_FILENO);
		close(std_fd[2]);
	}
}

int				ft_add_process(t_elem left, t_elem right, int std_fd[3], int fd_to_close)
{
//	ft_dprintf(2, "ADDPROCESS %s with {%d,%d,%d}, closes {%d}\n", right.v->left.c, std_fd[0], std_fd[1], std_fd[2], fd_to_close);
	pid_t		pid;
	t_process	process;


	if (!(pid = fork()))
	{
		if (fd_to_close != -1)
			close(fd_to_close);
		set_signals(CHILD);
		ft_stdredir(std_fd);
		return (i_execnode(left, right));
	}
	else
	{
	if (!(g_curjob.pgid))
		g_curjob.pgid = pid;
	setpgid(pid, g_curjob.pgid);
	process.pid = pid;
	process.status = RUNNING;
	ft_lstadd(&(g_curjob.process), ft_lstnew(&process, sizeof(t_process))); //a memcheck ?
	return (0);
	}
}
