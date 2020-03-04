/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_prio.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:31:39 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/18 11:01:23 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;

void		ft_set_prio(void)
{
	int			i;
	t_list		*voyager;
	t_job		*job;

	i = 0;
	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = voyager->content;
		if (i < 2 && !(job->status & BACKGROUND))
			g_jcont.active_jobs[i++] = job->nbr;
		if (i > 1)
			return ;
		voyager = voyager->next;
	}
	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = voyager->content;
		if (i < 2 && (job->status & BACKGROUND))
			g_jcont.active_jobs[i++] = job->nbr;
		if (i > 1)
			return ;
		voyager = voyager->next;
	}
}
