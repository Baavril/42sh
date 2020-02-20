/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/20 13:09:06 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

extern int		g_mode;
t_jcont			g_jcont = {NULL, 1, {0, 0}};
t_job			g_curjob = {NULL, 0, 0, NULL, 0};
char			*g_bgpid = NULL;

int			ft_launch_job(void)
{
	t_job		*job;
	int			ret_status;

	if (!(g_curjob.process))
	{
		ft_strdel(&(g_curjob.cmd));
		return (0);
	}
	if (!(job = ft_add_job()))
		return (e_cannot_allocate_memory);
	if (g_mode & BACKGROUND)
	{
		ft_dprintf(STDERR_FILENO, "[%i] %i\n", job->nbr, job->pgid);
		ft_strdel(&g_bgpid);
		g_bgpid = ft_itoa(job->pgid);
		return (0);
	}
	ret_status = ft_wait_foreground(job);
	if (!WIFSTOPPED(job->status))
		ft_pop_job(job->nbr);
	return (ret_status);
}
