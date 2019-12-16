/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 19:37:10 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

t_jcont				g_jcont = {NULL, 1, {0, 0}};
t_job				g_curjob = {NULL, 0, 0, NULL, 0};

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
	t_job		*job;
	sigset_t	wakeup_sig;
	int			ret_status;

	ft_dprintf(2, "\n\n>>>> LAUNCH JOB <<<<\n");
	job = ft_add_job(status, cmd); //may fail due to malloc
	if (ISBACKGROUND(status))
	{
		killpg(job->pgid, SIGUSR1);
		return (0);
	}
	sigfillset(&wakeup_sig);
	sigdelset(&wakeup_sig, SIGUSR1);
	while (!ft_isready(job)) //Attente de la creation et mise en place de tout les fils
		sigsuspend(&wakeup_sig);
	tcsetpgrp(STDIN_FILENO, job->pgid); //mise au premier plan vis-a-vis le term
	sigfillset(&wakeup_sig);
	sigdelset(&wakeup_sig, SIGCHLD);
	killpg(job->pgid, SIGUSR1);
	while (ISRUNNING(job->status)) //Attente de l'arret/suspension de tout les fils
		sigsuspend(&wakeup_sig);
	tcsetpgrp(STDIN_FILENO, getpid()); //mise au premier plan vis-a-vis du shell
	ret_status = job->status;
	if (job && !WIFSTOPPED(job->status))
		ft_pop_job(job->nbr);
	return (ret_status);
}
