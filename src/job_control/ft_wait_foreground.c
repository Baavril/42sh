/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_foreground.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:40:42 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/18 16:09:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int		ft_wait_foreground(t_job* job)
{
	sigset_t	wakeup_sig;

	tcsetpgrp(STDIN_FILENO, job->pgid); //mise au premier plan vis-a-vis le term
	sigfillset(&wakeup_sig);
	sigdelset(&wakeup_sig, SIGCHLD);
	kill(job->pgid, SIGUSR1);
	ft_dprintf(2, "Job in foreground: %i\n", tcgetpgrp(0));
	while (ISRUNNING(job->status)) //Attente de l'arret/suspension de tout les fils
		sigsuspend(&wakeup_sig);
	tcsetpgrp(STDIN_FILENO, getpid());
	if (WIFSTOPPED(job->status))
		return (job->status);
	return (((t_process*)(job->process->content))->status);
}
