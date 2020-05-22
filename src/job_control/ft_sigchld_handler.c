/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigchld_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:50:48 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/22 14:42:24 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;
extern t_job		g_curjob;

void				ft_sigchld_handler(int nbr)
{
	int			ret_status;
	int			pid;
	t_job		*job;
	t_process	*process;

	(void)nbr;
	while ((pid = waitpid(-1, &ret_status, WUNTRACED | WNOHANG)) > 0)
	{
		if ((job = ft_get_job_pgid(pid)))
		{
			job->status = ret_status | (BACKGROUND & job->status);
			process = ft_get_process_from_job(job, pid);
		}
		else if (!(process = ft_get_process_pid(pid))
				&& !(process = ft_get_process_from_job(&g_curjob, pid)))
			continue ;
		process->status = ret_status;
	}
	ft_update_job_status();
}
