/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resume_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 11:40:15 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/07 11:18:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "jcont.h"

extern char			*g_progname;
extern t_jcont		g_jcont;

static void			ft_set_running(t_job *job)
{
	t_list		*voyager;
	t_process	*process;

	voyager = job->process;
	while (voyager)
	{
		process = (t_process*)(voyager->content);
		if (WIFSTOPPED(process->status))
			process->status = RUNNING;
		voyager = voyager->next;
	}
	job->status = RUNNING;
}

int					ft_resume_in_fg(t_job *job)
{
	int		ret_status;

	if (g_jcont.active_jobs[0] != job->nbr)
		g_jcont.active_jobs[1] = g_jcont.active_jobs[0];
	g_jcont.active_jobs[0] = job->nbr;
	if (WIFSTOPPED(job->status))
	{
		if (!killpg(job->pgid, SIGCONT))
			ft_set_running(job);
		else
		{
			ft_dprintf(2, "%s: fg: error while sending signal(SIGCONT).", \
																	g_progname);
			return (1);
		}
	}
	ret_status = ft_wait_foreground(job);
	return (ret_status);
}

int					ft_resume_in_bg(t_job *job)
{
	if (!killpg(job->pgid, SIGCONT))
	{
		job->status = RUNNING | BACKGROUND;
		ft_set_prio();
		return (0);
	}
	ft_dprintf(2, "%s: bg: error while sending continue signal(SIGCONT).",
													g_progname);
	return (1);
}
