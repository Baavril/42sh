/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:57:05 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/18 12:18:05 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "jcont.h"

extern t_jcont		g_jcont;
extern char			*g_progname;

static int			ft_bg_prio_job(void)
{
	t_job		*job;

	if (!(g_jcont.jobs))
		ft_dprintf(STDERR_FILENO, "%s: bg: no current job.\n", g_progname);
	else if ((job = ft_get_job_nbr(g_jcont.active_jobs[0])))
	{
		if ((job->status & BACKGROUND) && (job->status & RUNNING))
			ft_dprintf(STDERR_FILENO,
							"%s: bg: job %i is already in background.\n",
							g_progname, g_jcont.active_jobs[0]);
		else if (!WIFSTOPPED(job->status))
			ft_dprintf(STDERR_FILENO,
							"%s: bg: job has terminated.\n", g_progname);
		else
			return (ft_resume_in_bg(job));
	}
	return (1);
}

/*
** Took some freedom vis-a-vis the bash arguments of background builtin to match
** the jobs builtin arg (no need of '%' to get the job-id).
*/

int					cmd_bg(int ac, char **av)
{
	t_job		*job;
	int			ret;
	int			i;

	i = 0;
	ret = (ac == 1) ? ft_bg_prio_job() : 0;
	while (++i < ac)
	{
		if (ft_isnumber(av[i]) && (job = ft_get_job_nbr(ft_atoi(av[i]))))
		{
			if (WIFSTOPPED(job->status))
				ret += ft_resume_in_bg(job);
			else if ((job->status & BACKGROUND) && (job->status & RUNNING))
				ft_dprintf(STDERR_FILENO,
							"%s: bg: job %s is already in background.\n",
							g_progname, av[i]);
			else if (++ret)
				ft_dprintf(STDERR_FILENO,
							"%s: bg: job has terminated.\n", g_progname);
		}
		else if (++ret)
			ft_dprintf(STDERR_FILENO,
							"%s: bg: %s: no such job.\n", g_progname, av[i]);
	}
	return (ret ? 1 : 0);
}
