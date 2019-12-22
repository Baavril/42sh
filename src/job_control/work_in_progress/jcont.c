/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/12 01:11:18 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "jcont.h"
//#include "parser.h"

t_jcont		g_jcont = {NULL, 1, {0, 0}};
t_list		*g_proclist = NULL;
pid_t		g_pgid = 0;

t_job		*ft_add_job(int status, char *cmd)
{
	t_job	new;
	t_list	*new_front;

	ft_putendl("ft_add_job");
	if (!g_proclist || (cmd && !(new.cmd = ft_strdup(cmd))))
		return (NULL);
	new.pgid = g_pgid;
	new.nbr = (g_jcont.job_nbr)++;
	new.status = status | RUNNING;
	new.process = g_proclist;
	g_proclist = NULL;
	ft_dprintf(2, ">>> job pgid: %i <<<\n", new.pgid);
	g_pgid = 0;
	if (!(new_front = ft_lstnew(&new, sizeof(t_job))))
	{
		free(new.cmd);
		return (NULL);
	}
	ft_lstadd(&(g_jcont.jobs), new_front);
	ft_set_prio();
	ft_putendl("ft_add_job_job_create");
	return (new_front->content);
}

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

int			ft_add_process(void ft_exec(void), int std_fd[3], int fd_to_close[2])
{
	pid_t		pgid;
	pid_t		pid;
	t_process	process;

	if (!(pid = fork()))
	{
		ft_set_child_signal();
		if (fd_to_close[0] != -1)
			close(fd_to_close[0]);
		if (fd_to_close[1] != -1)
			close(fd_to_close[1]);
		pgid = (g_pgid) ? g_pgid : getpid();
//	ft_dprintf(2, "pgid in son: %i\n", pgid);
		setpgid(getpid(), pgid);
		ft_stdredir(std_fd);
		(*ft_exec)();
//		ft_exec_ast_node(ast_node);
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
	t_job		*job;
	t_process	*process;
	int			ret_status;
	pid_t		pid;

	ft_putendl("ft_launch_job");
	job = ft_add_job(status, cmd);
	ft_dprintf(2, ">>> job pgid: %i <<<\n", job->pgid);
	ft_putendl("ft_add_job_end");
	printf("job_address %p\n", job);
	if (ISFOREGROUND(status))
	{
	ft_putendl("FOREGROUND_TEST");
		ft_dprintf(2, "Return of tcsetpgrp: %i for son pgid: %i\n", tcsetpgrp(STDIN_FILENO, job->pgid), job->pgid);
	ft_putendl("wait_start");
		while ((pid = waitpid(-job->pgid, &ret_status, WUNTRACED)) != -1)
		{
			if (!(process = ft_get_process_from_job(job, pid)))
				continue ;
			process->status = ret_status;
			if (pid == job->pgid)
				job->status = ret_status;
		}
	ft_putendl("wait_end");
		tcsetpgrp(STDIN_FILENO, getpid());
	ft_putendl("apres tcsetpgrp");
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
