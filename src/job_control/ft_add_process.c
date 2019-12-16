/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 15:51:32 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 18:27:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

t_list			*g_proclist = NULL;
pid_t			g_pgid = 0;


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

void			ft_catch_sigusr1(int nbr)
{
	(void)nbr;
}

void			ft_set_child_signal(int shell_pid)//Cela suffira-t-il ?
{
	sigset_t		wakeup_sig;

	struct sigaction	action;

	ft_bzero(&action, sizeof(sigaction));
	action.sa_handler = &ft_catch_sigusr1;
	sigaction(SIGUSR1, &action, NULL);

	sigfillset(&wakeup_sig);
	sigdelset(&wakeup_sig, SIGUSR1);
	ft_dprintf(2, "In Son: WAITING for the top a la vachette\n");
	kill(shell_pid, SIGUSR1);
	sigsuspend(&wakeup_sig);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	ft_dprintf(2, "In SOn: >>>>> top a la vachette <<<<<<<<<<<<\n");
}


int				ft_add_process(t_node ast_node, int std_fd[3], int fd_to_close)
{
	ft_printf("ADDPROCESS %s with {%d,%d,%d}, closes {%d}\n", ast_node.right.v->left.c, std_fd[0], std_fd[1], std_fd[2], fd_to_close);
	pid_t		pgid;
	pid_t		pid;
	t_process	process;

	int shell_pid = getpid();

	if (!(pid = fork()))
	{
		if (fd_to_close != -1)
			close(fd_to_close);
		pgid = (g_pgid) ? g_pgid : getpid();
		//	ft_dprintf(2, "pgid in son: %i\n", pgid);
		ft_dprintf(2, "add process: In son: %i setpgid ret: %i\n", getpid(), setpgid(getpid(), pgid));
		ft_dprintf(2, "add process: In son: %i pgid of call: %i       actualpgid: %i\n", getpid(), pgid, getpgrp());
		ft_set_child_signal(shell_pid);
		ft_stdredir(std_fd);
		ast_node.f(ast_node.left, ast_node.right);
	}
	if (!g_pgid)
		g_pgid = pid;
	ft_dprintf(2, "pgid: %i\n", g_pgid);
	process.pid = pid;
	process.ready = 0;
	process.status = RUNNING;
	ft_lstadd(&g_proclist, ft_lstnew(&process, sizeof(t_process))); //a memcheck ?
	return (0);
}

