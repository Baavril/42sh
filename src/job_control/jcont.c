/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 18:33:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

t_jcont				g_jcont = {NULL, 1, {0, 0}};
extern t_list		*g_proclist;
extern pid_t		g_pgid;

static int			ft_accumulate_ready(t_list *proclist)
{
	t_process	*process;

	if (!proclist)
		return (1);
	process = (t_process*)(proclist->content);
	return (process->ready & ft_accumulate_ready(proclist->next));
}

int			ft_isready(t_job *job)
{
	return (ft_accumulate_ready(job->process));
}

int			ft_launch_job(char *cmd, int status)
{
	sigset_t	wakeup_sig;
	t_job		*job;
	int			ret_status;

	ft_dprintf(2, "\n\n>>>> LAUNCH JOB <<<<\n");
	job = ft_add_job(status, cmd);
	//	ft_dprintf(2, ">>> job pgid: %i <<<\n", job->pgid);
	ft_dprintf(2, "ft_add_job_end\n");
	//	ft_dprintf(2, "job_address %p\n", job);
	if (ISBACKGROUND(status))
	{
		killpg(job->pgid, SIGUSR1);
		return (0);
	}
	sigfillset(&wakeup_sig);
	sigdelset(&wakeup_sig, SIGUSR1);
	ft_dprintf(2, "FOREGROUND_TEST\n");

	int j = 1;

	while (!ft_isready(job))
	{
		ft_dprintf(2, "\nJE SUIS PAS PRET\n\n");
		sigsuspend(&wakeup_sig);
	}
	ft_dprintf(2, "Return of tcsetpgrp: %i for son pgid: %i\n", j = tcsetpgrp(STDIN_FILENO, job->pgid), job->pgid);
	sigfillset(&wakeup_sig);
	sigdelset(&wakeup_sig, SIGCHLD);
	killpg(job->pgid, SIGUSR1);

	ft_dprintf(2, "wait_start\n");
	while (ISRUNNING(job->status))
		sigsuspend(&wakeup_sig);
	j = tcsetpgrp(STDIN_FILENO, getpid());
	ft_dprintf(2, "apres tcsetpgrp (ret: %i) Job status: %i   ISRUNNING(job): %i\n", j, job->status, ISRUNNING(job->status));
	ret_status = ((t_process*)job->process->content)->status;
	if (job && !WIFSTOPPED(job->status))
	{
		ft_dprintf(2, "plop\n");
		ft_pop_job(job->nbr);
	}
	return (ret_status);
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
		ft_dprintf(2, "plip\n");
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
