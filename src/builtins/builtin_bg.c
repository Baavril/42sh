/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:57:05 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/18 15:24:48 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "jcont.h"

extern t_jcont		g_jcont;
extern char			*g_progname;

int					ft_resume_in_bg(t_job *job)
{
	if (!kill(-job->pgid, SIGCONT))
	{
		job->status = RUNNING | BACKGROUND;
		ft_set_prio();
		return (0);
	}
	ft_dprintf(2, "%s: bg: error while sending continue signal(SIGCONT).", g_progname);
	return (1);
}

/* Took some freedom vis-a-vis the bash arguments of background builtin to match
** the jobs builtin arg (no need of '%' to get the job-id).
*/

int					cmd_bg(int ac, char **av)
{
	t_job		*job;
	int			ret;
	int			i;

	ret = 0;
	if (ac == 1)
	{
		if (!(g_jcont.jobs) && (++ret))
			ft_dprintf(STDERR_FILENO, "%s: bg: no current job.\n", g_progname);
		else if ((job = ft_get_job_nbr(g_jcont.active_jobs[0])))
		{
			if (ISBACKGROUND(job->status) && ISRUNNING(job->status))
				ft_dprintf(STDERR_FILENO, "%s: bg: job %i is already in background.\n", g_progname, g_jcont.active_jobs[0]);
			else if (!WIFSTOPPED(job->status) && (++ret))
				ft_dprintf(STDERR_FILENO, "%s: bg: job has terminated.\n", g_progname);
			else
				ret = ft_resume_in_bg(job);
		}
		return (ret);
	}
	i = 0;
	while (++i < ac)
	{
		if (ft_isnumber(av[1]) && (job = ft_get_job_nbr(ft_atoi(av[1]))))
		{
			if (WIFSTOPPED(job->status))
				ret += ft_resume_in_bg(job);
			else if (ISBACKGROUND(job->status) && ISRUNNING(job->status))
				ft_dprintf(STDERR_FILENO, "%s: bg: job %s is already in background.\n", g_progname, av[1]);
			else if (++ret)
				ft_dprintf(STDERR_FILENO, "%s: bg: job has terminated.\n", g_progname);
		}
		else if (++ret)
			ft_dprintf(STDERR_FILENO, "%s: bg: %s: no such job.\n", g_progname, av[1]);
	}
	return (ret ? 1 : 0);
}
