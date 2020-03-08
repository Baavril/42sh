/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/06 12:35:24 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

t_jcont			g_jcont = {NULL, 1, {0, 0}};
t_job			g_curjob = {NULL, 0, 0, NULL, 0};
char			*g_bgpid = NULL;
extern int		g_mode;
extern int		g_retval;

int			ft_launch_job(void)
{
	t_job		*job;
	int			ret_status;

	ret_status = 0;
	if (!(g_curjob.process))
	{
		ft_strdel(&(g_curjob.cmd));
		return (0);
	}
	if (!(job = ft_add_job()))
		return (e_cannot_allocate_memory);
	if (g_mode & BACKGROUND)
	{
		ft_strdel(&g_bgpid);
		g_bgpid = ft_itoa(job->pgid);
		if (!(g_mode & FORK_SHELL))
			ft_dprintf(STDERR_FILENO, "[%i] %i\n", job->nbr, job->pgid);
		else
			ret_status = ft_wait_background(job);
		return (ret_status);
	}
	ret_status = ft_wait_foreground(job);
	return (ret_status);
}
