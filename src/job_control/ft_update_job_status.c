/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:01:09 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/14 20:35:05 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;

static int			ft_accumulate_proc_status(t_list *proclist)
{
	t_process	*process;

	if (!proclist)
		return (0);
	process = (t_process*)(proclist->content);
	return (process->status | ft_accumulate_proc_status(proclist->next));
}

void		ft_check_bgstatus(void)
{
	size_t		i;
	int			job_topop[g_jcont.job_nbr];
	int			status;
	t_job		*job;
	t_list		*voyager;

	i = 0;
	if (!(voyager = g_jcont.jobs))
		return ;
	while (voyager)
	{
		job = voyager->content;
		status = ft_accumulate_proc_status(job->process);
		if (ISBACKGROUND(job->status) && WIFEXITED(job->status))
			job_topop[i++] = job->nbr;
		voyager = voyager->next;
	}
	while (i--)
	{
		ft_print_job(ft_get_job_nbr(job_topop[i]), 0);
		ft_pop_job(job_topop[i]);
	}
}

void				ft_update_job_status(void)
{
	int			status;
	t_list		*voyager;

	voyager = g_jcont.jobs;
	while (voyager)
	{
		status = ft_accumulate_proc_status(((t_job*)voyager->content)->process);
		if (WIFSTOPPED(status))
			((t_job*)voyager->content)->status = status;
		else if (WIFEXITED(status))
			((t_job*)voyager->content)->status &= ~RUNNING & ~_WSTOPPED;
		else
		{
			((t_job*)voyager->content)->status &= ~RUNNING;
			((t_job*)voyager->content)->status |= MAJOR_FAILLURE;// un certain nombre de programmes ont fail (signal != stop) et les autres ont retourne
		}
		voyager = voyager->next;
	}
}
