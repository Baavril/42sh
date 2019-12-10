/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_job_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:01:09 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/10 16:35:51 by tgouedar         ###   ########.fr       */
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

void				ft_update_job_status(void)
{
	int			status;
	t_list		*voyager;

	voyager = g_jcont.jobs;
	while (voyager)
	{
		status = ft_accumulate_proc_status(voyager->process);
		if (WIFSTOPPED(status))
			((t_job*)voyager->content)->status = status;
		else if (WIFEXITED(status))
			((t_job*)voyager->content)->status &= ~RUNNING;
		else
		{
			((t_job*)voyager->content)->status &= ~RUNNING;
			((t_job*)voyager->content)->status |= MAJOR_FAILLURE; // un certain nombre de programmes ont fail (signal != stop) et les autres ontourn
		}
		voyager = voyager->next;
	}
}
