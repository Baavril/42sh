/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigchld_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:50:48 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/10 16:34:06 by tgouedar         ###   ########.fr       */
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

	while ((pid = waitpid(WAIT_ANY, &ret_status, WUNTRACED | WNOHANG)) > 0)
	{
		if (job = ft_get_job_pgid(pid))
		{
			job->status = ret_status;
		if ((process = ft_get_process_from_job(job, pid)))
			process->status = ret_status;
		}
		else if (!(process = ft_get_process_pid(pid)))
			continue ;
		process->status = ret_status; // et peut etre des trucs a moi.
	}
	ft_update_job_status();
}
