/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:17:51 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/18 11:05:41 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "jcont.h"

extern t_jcont		g_jcont;
extern char			*g_progname;

void				ft_set_running(t_job *job)
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
	if (!WIFSTOPPED(job->status))
		ft_pop_job(job->nbr);
	return (ret_status);
}

/*
** Took some freedom vis-a-vis the bash arguments of background builtin to match
** the jobs builtin arg (no need of '%' to get the job-id).
** I supposed it would only interpret one argument since bash's fg seems to
** ignore any of the other arguments. This builtin has no options.
*/

int					cmd_fg(int ac, char **av)
{
	t_job	*job;
	int		ret;

	ret = 0;
	if (ac == 1)
	{
		if (!(g_jcont.jobs) && (++ret))
			ft_dprintf(STDERR_FILENO, "%s: fg: no current job.\n", g_progname);
		else if ((job = ft_get_job_nbr(g_jcont.active_jobs[0])))
		{
			if (((job->status & BACKGROUND) && (job->status & RUNNING))
			|| WIFSTOPPED(job->status))
				ret = ft_resume_in_fg(job);
			else if (WIFEXITED(job->status) && (++ret))
				ft_dprintf(STDERR_FILENO, "%s: fg: job has terminated.\n", g_progname);
		}
	}
	else if (ft_isnumber(av[1]) && (job = ft_get_job_nbr(ft_atoi(av[1]))))
	{
		if (WIFSTOPPED(job->status) || (job->status & BACKGROUND))
			ret = ft_resume_in_fg(job);
		else if (WIFEXITED(job->status) && (++ret))
			ft_dprintf(STDERR_FILENO, "%s: fg: job has terminated.\n", g_progname);
	}
	else if (++ret)
		ft_dprintf(STDERR_FILENO, "%s: fg: %s: no such job.\n", g_progname, av[1]);
	return (ret);
}
