/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_foreground.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:40:42 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/01 17:17:13 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

extern int		g_retval;

int				ft_wait_foreground(t_job *job)
{
	int			ret_status;
	sigset_t	wakeup_sig;

	tcsetpgrp(STDIN_FILENO, job->pgid);
	sigfillset(&wakeup_sig);
	sigdelset(&wakeup_sig, SIGCHLD);
	while (job->status & RUNNING)
		sigsuspend(&wakeup_sig);
	tcsetpgrp(STDIN_FILENO, getpid());
	if (WIFSTOPPED(job->status))
	{
		ret_status = job->status;
		g_retval = WHARD_EXIT | WSTOPSIG(ret_status);
	}
	else
	{
		ret_status = ((t_process*)(job->process->content))->status;
		if (WIFEXITED(ret_status))
			g_retval = WEXITSTATUS(ret_status);
		else
			g_retval = WHARD_EXIT | WTERMSIG(ret_status);
	}
	return (ret_status);
}
