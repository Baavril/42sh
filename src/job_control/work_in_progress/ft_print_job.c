/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:25:57 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/07 10:22:31 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

static void		ft_statestring(char status[MAX_STATE_LEN], int status) //d'autres messages ?
{
	int		sig;

	if (ISRUNNING(status))
		ft_memcpy(&(status[0]), "Running\0", 8);
	else if (WIFSTOPPED(status))
	{
		sig = WSTOPSIG(status);
		ft_memcpy(&(status[0]), "Stopped(", 8);
		if (sig == SIGTSTP)
			ft_memcpy(&(status[8]), "SIGTSTP)\0", 9);
		if (sig == SIGSTOP)
			ft_memcpy(&(status[8]), "SIGSTOP)\0", 9);
	}
	else if (WIFEXITED(status))
		ft_memcpy(&(status[0]), "Done\0", 5);
}

void			ft_print_job(t_job *job, int opt)
{
	char	status[MAX_STATE_LEN];
	char	prio;

	if (!(job))
		return ;
	ft_statestring(status, job->status);
	prio = ' ';
	if (g_jcont.active_jobs[0] == job->nbr)
		prio = '+';
	else if (g_jcont.active_jobs[1] == job->nbr)
		prio = '-';
	if (opt == OPT_L)
		printf("[%i]%-2c %i%-*s%s\n", job->nbr, prio, job->pgid, MAX_STATE_LEN, status, job->cmd);
	else if (opt == OPT_P)
		printf("%i\n", job->pgid);
	else
		printf("[%i]%-2c %-*s%s\n", job->nbr, prio, MAX_STATE_LEN, status, job->cmd);
}
