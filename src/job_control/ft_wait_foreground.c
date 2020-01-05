/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_foreground.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:40:42 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/05 15:32:51 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int		ft_wait_foreground(t_job *job)
{
	sigset_t	wakeup_sig;

	tcsetpgrp(STDIN_FILENO, job->pgid);
	sigfillset(&wakeup_sig);
	sigdelset(&wakeup_sig, SIGCHLD);
//	ft_dprintf(2, "Job in foreground: %i\n", tcgetpgrp(0));
	while (ISRUNNING(job->status))
		sigsuspend(&wakeup_sig);
//	ft_dprintf(2, "JOB return status: %i is running : %i\n", job->status, ISRUNNING(job->status));
	tcsetpgrp(STDIN_FILENO, getpid());
//	ft_dprintf(2, "Shell pid: %i          Job in foreground: %i\n", getpid(), tcgetpgrp(0));
	if (WIFSTOPPED(job->status))
		return (job->status);
	return (((t_process*)(job->process->content))->status);
}
