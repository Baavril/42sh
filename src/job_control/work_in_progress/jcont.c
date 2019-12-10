/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/10 16:12:29 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <stdio.h>

t_jcont		g_jcont = {NULL, 1, {0, 0}};
t_list		*g_proclist = NULL;
pid_t		g_pgid = 0;

t_job		*ft_add_job(int status, char *cmd)
{
	t_job	new;
	t_list	*new_front;

	if (!g_proclist || (cmd && !(new.cmd = ft_strdup(cmd))))
		return (NULL);
	if (!(new_front = ft_lstnew(&new, sizeof(t_job))))
	{
		free(new.cmd);
		return (NULL);
	}
	new.pgid = g_pgid;
	new.nbr = (g_jcont.job_nbr)++;
	new.status = status;
	new.process = g_proclist;
	g_proclist = NULL;
	g_pgid = 0;
	ft_lstadd(&(g_jcont.jobs), new_front);
	ft_set_prio();
	return (&new);
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
	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, &ft_sigchild_handler);
}

int			ft_add_process(void *ast_node, int std_fd[3], int fd_to_close[2])
{
	pid_t		pgid;
	pid_t		pid;
	t_process	process;

	if (pid = fork())
	{
		if (fd_to_close[0] != -1)
			close(fd_to_close[0]);
		if (fd_to_close[1] != -1)
			close(fd_to_close[1]);
		pgid = (g_pgid) ? g_pgid : getpid();
		setpgid(pgid, getpid())
		ft_stdredir(std_fd);
		ft_set_child_signal();
//		ft_exec_ast_node(ast_node);
	}
	if (!g_pgid)
		g_pgid = pid;
	process.pid = pid;
	process.status = 0;
	ft_lstadd(&g_proclist, ft_lstnew(&process, sizeof(t_process))); //a memcheck ?
	return (0);
}

int			ft_launch_job(char *cmd, int status)
{
	t_job	*job;
	int		ret_status;
	pid_t	pid;

	job = ft_add_job(cmd, status);
	if (ISFOREGROUND(status))
	{
		tcsetpgrp(STDIN_FILENO, job->pgid);
		while ((pid = waitpid(-job->pgid, &ret_status, WUNTRACED)) != -1)
		{
			if (pid == job->pgid)
				job->status = ret_status;
			process = ft_get_process_from_job(job, pid);
			process->status = ret_status;
		}
		tcsetpgrp(STDIN_FILENO, getpid());
		ret_status = job->status;
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

int			ft_launch_job(pid_t pid, char *cmd, int flag)
{
	int		ret_status;
	t_job	*new_job;

	if (ISFOREGROUND(flag))
		tcsetpgrp(STDIN_FILENO, pid);
	if (ISFOREGROUND(flag))
		waitpid(-pid, &ret_status, WUNTRACED);
	return (SUCESS);
}

void		ft_check_bgstatus(void)
{
	size_t	i;
	int		job_topop[g_jcont.job_nbr];
	t_job	*job;
	t_list	*voyager;

	i = 0;
	if (!(voyager = g_jcont.job_list))
		return ;
	while (voyager)
	{
		job = voyager->content;
		if (ISBACKGROUND(job->status) && WIFEXITED(job->status))
			job_topop[i++] = job_nbr->nbr;
		voyager = voyager->next;
	}
	while (i--)
	{
		ft_print_job(job_topop[i], 0);
		ft_pop_job(job_topop[i]);
	}
}
