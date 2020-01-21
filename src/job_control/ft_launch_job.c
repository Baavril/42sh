/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/21 11:15:24 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

t_jcont				g_jcont = {NULL, 1, {0, 0}};
t_job				g_curjob = {NULL, 0, 0, NULL, 0};
int				g_retval;

int			ft_launch_job(char *cmd, int status)
{
	t_job		*job;
	int			ret_status;

	if (!(g_curjob.process))
		return (0);
	job = ft_add_job(status, cmd); //may fail due to malloc
	if (status & BACKGROUND)
		return (0);
	ret_status = ft_wait_foreground(job);
	if (!WIFSTOPPED(job->status))
		ft_pop_job(job->nbr);
	g_retval = ret_status;
	return (ret_status);
}
