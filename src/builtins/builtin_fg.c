/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:17:51 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 16:22:47 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "jcont.h"

extern t_jcont		g_jcont;
extern char			*g_progname;

int				ft_resume_in_fg(t_job *job)
{
	pid_t			pid;
	int				ret_status;
	t_process		*process;

/*	sigemptyset(&wakeup_sig);
	//sigaddset(&wakeup_sig, SIGCHLD);
	sigaction(SIGCHLD, &(struct sigaction){.sa_handler = ft_sigchld_handler }, 0);

	extern int errno;
	int j;

	ft_dprintf(2, "Return of tcsetpgrp: %i for son pgid: %i\n", j = tcsetpgrp(STDIN_FILENO, job->pgid), job->pgid);
	if (j == -1) //fail de la mise en avant
			{
				dprintf(2, "FAIL de prise de controle du terminal: ");
				if (errno == EINVAL)
					dprintf(2, "invalid PGID\n");
				if (errno == ENOTTY)
					dprintf(2, "On est pas dasn un terminal ?\n");
				if (errno == EPERM)
					dprintf(2, "Probleme de session ???? WUT\n");
				if (errno == EPERM)
					dprintf(2, "Probleme de Session\n");
			}
	if (WIFSTOPPED(job->status))
	{
		if (!killpg(-job->pgid, SIGCONT))
			job->status = RUNNING;
		else
		{
			ft_dprintf(2, "%s: fg: error while sending continue signal(SIGCONT).", g_progname);
			return (1);
		}
	}
	while (ISRUNNING(job->status))
		sigsuspend(&wakeup_sig);
	tcsetpgrp(STDIN_FILENO, getpid());
	ft_dprintf(2, "apres tcsetpgrp. Job status: %i   ISRUNNING(job): %i\n", job->status, ISRUNNING(job->status));
	ret_status = ((t_process*)job->process->content)->status;
	if (job && !WIFSTOPPED(job->status))
	{
		ft_dprintf(2, "plop\n");
		ft_pop_job(job->nbr);
	}
	return (ret_status);
}*/
	if (g_jcont.active_jobs[0] != job->nbr)
		g_jcont.active_jobs[1] = g_jcont.active_jobs[0];
	g_jcont.active_jobs[0] = job->nbr;
	while ((pid = waitpid(-job->pgid, &ret_status, WUNTRACED)) > 0)
	{
		if (!(process = ft_get_process_from_job(job, pid)))
			continue ;
		process->status = ret_status;
		if (pid == job->pgid)
			job->status = ret_status;
	}
	return (0);
}

/* Took some freedom vis-a-vis the bash arguments of background builtin to match
** the jobs builtin arg (no need of '%' to get the job-id).
** I supposed it would only interpret one argument since bash's fg seems to
** ignore any of the other arguments. This builtin has no options.
*/

int					cmd_fg(int ac, char **av)
{
	t_job		*job;
	int			ret;

	ret = 0;
	if (ac == 1)
	{
		if (!(g_jcont.jobs) && (++ret))
			ft_dprintf(STDERR_FILENO, "%s: fg: no current job.\n", g_progname);
		else if ((job = ft_get_job_nbr(g_jcont.active_jobs[0])))
		{
			if (WIFEXITED(job->status) && (++ret))
				ft_dprintf(STDERR_FILENO, "%s: fg: job has terminated.\n", g_progname);
			else if ((ISBACKGROUND(job->status) && ISRUNNING(job->status))
			|| WIFSTOPPED(job->status))
				ret = ft_resume_in_fg(job);
		}
	}
	else if (ft_isnumber(av[1]) && (job = ft_get_job_nbr(ft_atoi(av[1]))))
	{
		if (WIFSTOPPED(job->status) || ISBACKGROUND(job->status))
			ret = ft_resume_in_fg(job);
		else if (WIFEXITED(job->status) && (++ret))
			ft_dprintf(STDERR_FILENO, "%s: fg: job has terminated.\n", g_progname);
	}
	else if (++ret)
		ft_dprintf(STDERR_FILENO, "%s: fg: %s: no such job.\n", g_progname, av[1]);
	return (ret);
}
