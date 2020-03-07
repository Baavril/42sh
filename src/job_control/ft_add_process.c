/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 15:51:32 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/07 14:52:06 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "sig_handler.h"
#include "jcont.h"
#include "parser.h"

extern int		g_mode;
extern t_job	g_curjob;

void			ft_save_term_fd(int save_fd[3])
{
	save_fd[0] = dup2(STDIN_FILENO, RESERVED_INFD);
	save_fd[1] = dup2(STDOUT_FILENO, RESERVED_OUTFD);
	save_fd[2] = dup2(STDERR_FILENO, RESERVED_ERRFD);
}

void			ft_stdredir(int std_fd[3])
{
	if (std_fd[0] != STDIN_FILENO && std_fd[0] >= 0)
	{
		dup2(std_fd[0], STDIN_FILENO);
		close(std_fd[0]);
	}
	if (std_fd[1] != STDOUT_FILENO && std_fd[1] >= 0)
	{
		dup2(std_fd[1], STDOUT_FILENO);
		close(std_fd[1]);
	}
	if (std_fd[2] != STDERR_FILENO && std_fd[2] >= 0)
	{
		dup2(std_fd[2], STDERR_FILENO);
		close(std_fd[2]);
	}
}

int				ft_add_process(t_elem left, t_elem right, int std_fd[3],
															int fd_to_close)
{
	pid_t		pid;
	t_process	process;

	if (!(pid = fork()))
	{
		if (fd_to_close != -1)
			close(fd_to_close);
		set_signals((g_mode & FORK_SHELL) ? FORKED_CONTROL : CHILD);
		if (g_mode & FORK_SHELL)
		{
			ft_lstdel(&(g_curjob.process), &ft_free_proc);
			g_curjob.pgid = 0;
			ft_strdel(&(g_curjob.cmd));
			ft_free_jcont(NO_CHECK);
		}
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
		ft_lstadd(&(g_curjob.process), ft_lstnew(&process, sizeof(t_process)));
		return (0);
	}
}
