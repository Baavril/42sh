/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/14 20:27:52 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

t_jcont		g_jcont = {NULL, 1, {0, 0}};
t_list		*g_proclist = NULL;
pid_t		g_pgid = 0;

void		ft_stdredir(int std_fd[3])
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

void		ft_set_child_signal(void)//Cela suffira-t-il ?
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, &ft_sigchld_handler);
}

int			ft_add_process(t_node ast_node, int std_fd[3], int fd_to_close)
{
	ft_printf("ADDPROCESS %s with {%d,%d,%d}, closes {%d}\n",
			ast_node.right.v->left.c, std_fd[0], std_fd[1], std_fd[2], fd_to_close); 
	pid_t		pgid;
	pid_t		pid;
	t_process	process;

	if (!(pid = fork()))
	{
		ft_set_child_signal();
		if (fd_to_close != -1)
			close(fd_to_close);
		pgid = (g_pgid) ? g_pgid : getpid();
		//	ft_dprintf(2, "pgid in son: %i\n", pgid);
		ft_dprintf(2, "add process: In son: %i setpgid ret: %i\n", getpid(), setpgid(getpid(), pgid));
		ft_dprintf(2, "add process: In son: %i pgid of call: %i       actualpgid: %i\n", getpid(), pgid, getpgrp());
		ft_stdredir(std_fd);
		ast_node.f(ast_node.left, ast_node.right);
	}
	if (!g_pgid)
		g_pgid = pid;
	//	ft_dprintf(2, "pgid: %i\n", g_pgid);
	process.pid = pid;
	process.status = 0;
	ft_lstadd(&g_proclist, ft_lstnew(&process, sizeof(t_process))); //a memcheck ?
	return (0);
}

int			ft_launch_job(char *cmd, int status)
{
	sigset_t	wakeup_sig;
	t_job		*job;
	int			ret_status;


	ft_dprintf(2, "ft_launch_job\n");
	job = ft_add_job(status, cmd);
	//	ft_dprintf(2, ">>> job pgid: %i <<<\n", job->pgid);
	ft_dprintf(2, "ft_add_job_end\n");
	//	ft_dprintf(2, "job_address %p\n", job);
	if (ISFOREGROUND(status))
	{
		sigemptyset(&wakeup_sig);
		//sigaddset(&wakeup_sig, SIGCHLD);
		sigaction(SIGCHLD, &(struct sigaction){.sa_handler = ft_sigchld_handler }, 0);
		ft_dprintf(2, "FOREGROUND_TEST\n");
		ft_dprintf(2, "Return of tcsetpgrp: %i for son pgid: %i\n", tcsetpgrp(STDIN_FILENO, job->pgid), job->pgid);
		ft_dprintf(2, "wait_start\n");
		while (ISRUNNING(job->status))
			sigsuspend(&wakeup_sig);
		ft_dprintf(2, "wait_end\n");
		tcsetpgrp(STDIN_FILENO, getpid());
		ft_dprintf(2, "apres tcsetpgrp\n");
		ret_status = ((t_process*)job->process->content)->status;
		if (job && !WIFSTOPPED(job->status))
			ft_pop_job(job->nbr);
		return (ret_status);
	}
	return (0);
}

int			ft_pop_job(int nbr)
{
	t_list	*voyager;
	t_list	*tmp;

	if (!(voyager = g_jcont.jobs) || nbr >= g_jcont.job_nbr)
		return (1);
	if (!nbr)
		nbr = g_jcont.active_jobs[0];
	if (nbr == ((t_job*)(voyager->content))->nbr)
	{
		g_jcont.jobs = voyager->next;
		ft_lstdelone(&voyager, &ft_free_job);
	}
	else
	{
		while ((voyager->next) && ((t_job*)voyager->next->content)->nbr != nbr)
			voyager = voyager->next;
		if (!voyager->next)
			return (1);
		tmp = voyager->next;
		voyager->next = voyager->next->next;
		ft_lstdelone(&tmp, &ft_free_job);
	}
	ft_set_prio();
	g_jcont.job_nbr = (g_jcont.jobs) ? ((t_job*)(g_jcont.jobs->content))->nbr + 1 : 1;
	return (0);
}

void		ft_print_jobs(t_list *job_list, int opt)
{
	if ((job_list))
	{
		ft_print_jobs(job_list->next, opt);
		ft_print_job(job_list->content, opt);
	}
}
