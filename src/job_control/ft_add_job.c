/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:36:57 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/19 19:34:22 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "jcont.h"

extern int			g_mode;
extern t_jcont		g_jcont;
extern t_job		g_curjob;
extern int			g_fd[3];

t_job				*ft_add_job(void)
{
	t_list	*new_front;

	if (!(g_curjob.process))
	{
		ft_strdel(&(g_curjob.cmd));
		ft_bzero(&g_curjob, sizeof(t_job));
		return (NULL);
	}
	g_curjob.nbr = (g_jcont.job_nbr)++;
	g_curjob.status = g_mode | RUNNING;
	if (!(new_front = ft_lstnew(&g_curjob, sizeof(t_job))))
	{
		ft_strdel(&(g_curjob.cmd));
		ft_bzero(&g_curjob, sizeof(t_job));
		return (NULL);
	}
	ft_lstadd(&(g_jcont.jobs), new_front);
	ft_set_prio();
	ft_bzero(&g_curjob, sizeof(t_job));
	g_fd[0] = STDIN_FILENO;
	g_fd[1] = STDOUT_FILENO;
	g_fd[2] = STDERR_FILENO;
	return (new_front->content);
}
