/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_foreground.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:40:42 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/18 11:03:32 by tgouedar         ###   ########.fr       */
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
	while (job->status & RUNNING)
		sigsuspend(&wakeup_sig);
	tcsetpgrp(STDIN_FILENO, getpid());
	if (WIFSTOPPED(job->status))
		return (job->status);
	return (((t_process*)(job->process->content))->status);
}
