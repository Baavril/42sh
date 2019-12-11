/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:08:05 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/11 18:36:44 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "jcont.h"

extern t_jcont		g_jcont;
extern char			*g_progname;
extern int			optopt;
extern int			optind;
extern int			opterr;

int					cmd_jobs(int ac, char **av)
{
	int			ret;
	t_job		*job;
	size_t		i;
	int			opt;

	opterr = 0;
	optind = 1;
	while ((ret = getopt(ac, av, JOBS_OPT)) > 0)
	{
		if (ret == '?')
		{
			ft_dprintf(STDERR_FILENO, "%s: jobs: -%c: invalid option.\n", g_progname, optopt);
			ft_dprintf(STDERR_FILENO,"jobs: usage: jobs [-lp] [jobspec ...]");
		}
		else if (ret == 'l')
			opt = L_OPT;
		else if (ret == 'p')
			opt = P_OPT;
	}
	i = optind;
	ret = 0;
	if (i == ac)
		ft_print_jobs(g_jcont.jobs, opt);
	while (i < ac)
	{
		if (ft_isnumber(av[i]) && (job = ft_get_job_nbr(ft_atoi(av[i]))))
			ft_print_job(job, opt);
		else if (++ret)
			ft_dprintf(STDERR_FILENO, "%s: jobs: %s: no such job.\n", g_progname, av[i]);
		i++;
	}
	return (ret > 0 ? 1 : 0);
}
