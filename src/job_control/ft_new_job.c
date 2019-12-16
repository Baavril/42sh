/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:36:57 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 19:35:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;
extern t_job		g_curjob;

t_job		*ft_add_job(int status, char *cmd)
{
	t_job	new;
	t_list	*new_front;

	if (!(g_curjob.process) || (cmd && !(new.cmd = ft_strdup(cmd))))
	{
		ft_bzero(&g_curjob, sizeof(t_job));
		return (NULL);
	}
	g_curjob.nbr = (g_jcont.job_nbr)++;
	g_curjob.status = status | RUNNING;
	if (!(new_front = ft_lstnew(&g_curjob, sizeof(t_job))))
	{
		free(g_curjob.cmd);
		ft_bzero(&g_curjob, sizeof(t_job));
		return (NULL);
	}
	ft_lstadd(&(g_jcont.jobs), new_front);
	ft_set_prio();
	ft_bzero(&g_curjob, sizeof(t_job));
	return (new_front->content);
}
