/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:56:52 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/12 13:18:31 by tgouedar         ###   ########.fr       */
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

int			ft_launch_job(char *cmd, int status)
{
	t_job		*job;
	int			ret_status;

	if (!(g_curjob.process))
		return (0);
	if (!(job = ft_add_job(status, cmd)))
		return (e_cannot_allocate_memory);
	if (status & BACKGROUND)
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
