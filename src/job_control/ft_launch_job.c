/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/02 16:15:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

t_jcont			g_jcont = {NULL, 1, {0, 0}};
t_job			g_curjob = {NULL, 0, 0, NULL, 0};
extern int		g_retval;
char			*g_bgpid = NULL;

int			ft_launch_job(char *cmd, int status)
{
	t_job		*job;
	int			ret_status;

	if (!(g_curjob.process))
		return (0);
	job = ft_add_job(status, cmd); //may fail due to malloc
	if (status & BACKGROUND)
	{
		ft_dprintf(STDERR_FILENO, "[%i] %i\n", job->nbr, job->pgid);
		g_bgpid = ft_itoa(job->pgid);
		return (0);
	}
	ret_status = ft_wait_foreground(job);
	if (!WIFSTOPPED(job->status))
		ft_pop_job(job->nbr);
	return (ret_status);
}
