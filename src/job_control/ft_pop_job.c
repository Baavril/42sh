/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:49:12 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/11 17:49:19 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

extern t_jcont		g_jcont;

static char			*get_sig_name(int sig)
{
	if (sig == SIGHUP)
		return (ft_strdup("Terminal Hang-up"));
	if (sig == SIGINT)
		return (ft_strdup("Interrupt program"));
	if (sig == SIGQUIT)
		return (ft_strdup("Program Quit"));
	if (sig == SIGILL)
		return (ft_strdup("Illegal Instruction"));
	if (sig == SIGTRAP)
		return (ft_strdup("Trace Trap"));
	if (sig == SIGABRT)
		return (ft_strdup("Program Abort"));
	if (sig == SIGFPE)
		return (ft_strdup("Floating-point Exception"));
	if (sig == SIGKILL)
		return (ft_strdup("Killed"));
	if (sig == SIGBUS)
		return (ft_strdup("Bus error"));
	if (sig == SIGSEGV)
		return (ft_strdup("Segmentation Fault"));
	if (sig == SIGSYS)
		return (ft_strdup("Non-existent Sys-call"));
	return (NULL);
}

static void			ft_notice_killed(t_job *job)
{
	int		sig;
	char	*sigmess;

	if (!WIFSTOPPED(job->status) && !WIFEXITED(job->status))
	{
		sig = WTERMSIG(job->status);
		if (!(sigmess = get_sig_name(sig)))
			return ;
		ft_dprintf(STDERR_FILENO, "%s: %i.\n", sigmess, sig);
		ft_strdel(&sigmess);
	}
}

int					ft_pop_job(int nbr)
{
	t_list	*voyager;
	t_list	*tmp;

	if (!(voyager = g_jcont.jobs) || nbr >= g_jcont.job_nbr)
		return (-1);
	if (!nbr)
		nbr = g_jcont.active_jobs[0];
	if (nbr == ((t_job*)(voyager->content))->nbr && (tmp = voyager))
		g_jcont.jobs = voyager->next;
	else
	{
		while ((voyager->next) && ((t_job*)voyager->next->content)->nbr != nbr)
			voyager = voyager->next;
		if (!voyager->next)
			return (1);
		tmp = voyager->next;
		voyager->next = voyager->next->next;
	}
	ft_notice_killed((t_job*)(tmp->content));
	ft_lstdelone(&tmp, &ft_free_job);
	ft_set_prio();
	g_jcont.job_nbr = (g_jcont.jobs) ?
								((t_job*)g_jcont.jobs->content)->nbr + 1 : 1;
	return (0);
}
