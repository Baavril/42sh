/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/02 19:45:03 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

t_jcont				g_jcont = {NULL, 1, {0, 0}};
t_job				g_curjob = {NULL, 0, 0, NULL, 0};

int			ft_launch_job(char *cmd, int status)
{
	t_job		*job;
	int			ret_status;

	if (!(g_curjob.process))
		return (0);
//	ft_dprintf(2, "\n\n>>>> LAUNCH JOB <<<<\n");
	job = ft_add_job(status, cmd); //may fail due to malloc
	if (ISBACKGROUND(status))
		return (0);
	ret_status = ft_wait_foreground(job);
//	ft_dprintf(2, "END of WAIT\n");
	if (!WIFSTOPPED(job->status))
		ft_pop_job(job->nbr);
	return (ret_status);
}
