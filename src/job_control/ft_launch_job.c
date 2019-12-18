/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 20:48:28 by tgouedar         ###   ########.fr       */
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
	sigset_t	wakeup_sig;
	t_job		*job;
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
	ret_status = ft_wait_foreground(job);
	if (!WIFSTOPPED(job->status))
		ft_pop_job(job->nbr);
	return (ret_status);
}
