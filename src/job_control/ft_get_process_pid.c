/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_process_pid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:28:28 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/16 19:38:18 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <unistd.h>

extern t_jcont		g_jcont;

t_process			*ft_get_process_from_job(t_job *job, pid_t pid)
{
	t_list		*voyager;
	t_process	*process;

	voyager = job->process;
	while (voyager)
	{
		process = (t_process*)(voyager->content);
		if (process->pid == pid)
			break ;
		voyager = voyager->next;
	}
	return ((voyager) ? process : NULL);
}

t_process			*ft_get_process_pid(pid_t pid)
{
	pid_t		pgid;
	t_list		*voyager;
	t_job		*job;
	t_process	*process;

	if ((pgid = getpgid(pid)) > 0)
	{
		if (!(job = ft_get_job_pgid(pgid)))
			return (NULL);
		return (ft_get_process_from_job(job, pid));
	}
	voyager = g_jcont.jobs;
	while (voyager)
	{
		if ((process = ft_get_process_from_job(voyager->content, pid)))
			return (process);
		voyager = voyager->next;
	}
	return (NULL);
}
