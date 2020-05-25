/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:57:05 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/18 12:18:05 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "jcont.h"
#include "error.h"

extern t_jcont		g_jcont;
extern char			*g_progname;

static int			ft_bg_prio_job(void)
{
	t_job		*job;

	if (!(g_jcont.jobs))
		psherror(31, "bg", e_builtin_type);
	else if ((job = ft_get_job_nbr(g_jcont.active_jobs[0])))
	{
		if ((job->status & BACKGROUND) && (job->status & RUNNING))
			psherror(32, "bg", e_builtin_type);
		else if (!WIFSTOPPED(job->status))
			psherror(33, "bg", e_builtin_type);
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
				psherror(32, "bg", e_builtin_type);
			else if (++ret)
				psherror(33, "bg", e_builtin_type);
		}
		else if (++ret)
			psherror(34, "bg", e_builtin_type);
	}
	return (ret ? 1 : 0);
}
