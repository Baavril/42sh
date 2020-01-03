/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:36:57 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/18 17:03:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "jcont.h"

extern t_jcont		g_jcont;
extern t_job		g_curjob;
extern int			g_fd[3];

t_job				*ft_add_job(int status, char *cmd)
{
	t_list	*new_front;

	if (!(g_curjob.process) || (cmd && !(g_curjob.cmd = ft_strdup(cmd))))
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
	g_fd[0] = STDIN_FILENO;
	g_fd[1] = STDOUT_FILENO;
	g_fd[2] = STDERR_FILENO;
	return (new_front->content);
}
