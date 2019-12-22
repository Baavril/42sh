/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigchld_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:50:48 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 20:35:22 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;

void		ft_sigchld_handler(int nbr)
{
	int			ret_status;
	int			pid;
	t_job		*job;
	t_process	*process;

	(void)nbr;

	while ((pid = waitpid(-1, &ret_status, WUNTRACED | WNOHANG)) > 0)
	{
	ft_dprintf(2, "handler: wait caught pid: %i\n", pid);
		if ((job = ft_get_job_pgid(pid)))
		{
			job->status = ret_status | (BACKGROUND &job->status);
			if (!(process = ft_get_process_from_job(job, pid)))
				continue ;
		}
		else if (!(process = ft_get_process_pid(pid)))
			continue ;
		ft_dprintf(2, "handler: process updated: %i\n", ret_status);
		process->status = ret_status; // et peut etre des trucs a moi.
	}
	ft_update_job_status();
}
