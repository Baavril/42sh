/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:08:05 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/18 11:07:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "jcont.h"
#include "ft_getopt.h"

extern t_jcont		g_jcont;
extern char			*g_progname;
extern int			g_optopt;
extern int			g_optind;
extern int			g_opterr;

void				ft_pop_done(void)
{
	size_t		i;
	int			job_topop[g_jcont.job_nbr];
	t_list		*voyager;
	t_job		*job;

	i = 0;
	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = voyager->content;
		if (!WIFSTOPPED(job->status) && !(job->status & RUNNING))
			job_topop[i++] = job->nbr;
		voyager = voyager->next;
	}
	while (i--)
		ft_pop_job(job_topop[i]);
	ft_set_prio();
}

static int			ft_parse_jobopt(int ac, char **av)
{
	int			ret;
	int			opt;

	g_opterr = 0;
	g_optind = 1;
	while ((ret = ft_getopt(ac, av, JOBS_OPT)) > 0)
	{
		if (ret == '?')
		{
			ft_dprintf(STDERR_FILENO, \
					"%s: jobs: -%c: invalid option.\n", g_progname, g_optopt);
			ft_dprintf(STDERR_FILENO, \
					"jobs: usage: jobs [-lp] [jobspec ...]\n");
			return (-1);
		}
		else if (ret == 'l')
			opt = L_OPT;
		else if (ret == 'p')
			opt = P_OPT;
	}
	return (opt);
}

int					cmd_jobs(int ac, char **av)
{
	int			ret;
	t_job		*job;
	int			i;
	int			opt;

	if ((opt = ft_parse_jobopt(ac, av)) < 0)
		return (2);
	i = g_optind;
	ret = 0;
	if (i == ac)
		ft_print_jobs(g_jcont.jobs, opt);
	while (i < ac)
	{
		if (ft_isnumber(av[i]) && (job = ft_get_job_nbr(ft_atoi(av[i]))))
			ft_print_job(job, opt);
		else if (++ret)
			ft_dprintf(STDERR_FILENO,
						"%s: jobs: %s: no such job.\n", g_progname, av[i]);
		i++;
	}
	ft_pop_done();
	return (ret > 0 ? 1 : 0);
}
