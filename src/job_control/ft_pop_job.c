/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:49:12 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 18:52:15 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

extern t_jcont		g_jcont;

int					ft_pop_job(int nbr)
{
	t_list	*voyager;
	t_list	*tmp;

	if (!(voyager = g_jcont.jobs) || nbr >= g_jcont.job_nbr)
		return (-1);
	if (!nbr)
		nbr = g_jcont.active_jobs[0];
	if (nbr == ((t_job*)(voyager->content))->nbr)
	{
		g_jcont.jobs = voyager->next;
		ft_lstdelone(&voyager, &ft_free_job);
		ft_dprintf(2, "Job was Popped\n");
	}
	else
	{
		while ((voyager->next) && ((t_job*)voyager->next->content)->nbr != nbr)
			voyager = voyager->next;
		if (!voyager->next)
			return (1);
		tmp = voyager->next;
		voyager->next = voyager->next->next;
		ft_lstdelone(&tmp, &ft_free_job);
	}
	ft_set_prio();
	g_jcont.job_nbr = (g_jcont.jobs) ? ((t_job*)(g_jcont.jobs->content))->nbr + 1 : 1;
	return (0);
}
