/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:17:51 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/18 12:12:45 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "jcont.h"
#include "error.h"

extern t_jcont		g_jcont;
extern char			*g_progname;

static int			ft_fg_prio_job(void)
{
	t_job	*job;

	if (!(g_jcont.jobs))
		psherror(31, "fg", e_builtin_type);
	else if ((job = ft_get_job_nbr(g_jcont.active_jobs[0])))
	{
		if (((job->status & BACKGROUND) && (job->status & RUNNING))
				|| WIFSTOPPED(job->status))
			return (ft_resume_in_fg(job));
		else if (WIFEXITED(job->status))
			psherror(33, "fg", e_builtin_type);
	}
	return (1);
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
		ret = ft_fg_prio_job();
	else if (ft_isnumber(av[1]) && (job = ft_get_job_nbr(ft_atoi(av[1]))))
	{
		if (WIFSTOPPED(job->status) || (job->status & BACKGROUND))
			ret = ft_resume_in_fg(job);
		else if (WIFEXITED(job->status) && (++ret))
			psherror(33, "fg", e_builtin_type);
	}
	else if (++ret)
		psherror(34, "fg", e_builtin_type);
	return (ret);
}
