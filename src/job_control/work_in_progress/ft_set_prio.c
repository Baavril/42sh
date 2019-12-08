/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_prio.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:31:39 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/08 11:59:21 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern t_jcont		g_jcont;

void		ft_set_prio(void)
{
	int		i;
	t_list	*voyager;
	t_job	*job;

	i = 0;
	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = voyager->content;
		if (i < 2 && ISFOREGROUND(job->status))
			g_jcont.active_jobs[i++] = job->nbr;
		if (i > 1)
			return ;
	}
	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = voyager->content;
		if (i < 2 && ISBACKGROUND(job->status))
			g_jcont.active_jobs[i++] = job->nbr;
		if (i > 1)
			return ;
	}
}
