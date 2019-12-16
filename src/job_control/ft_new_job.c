/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:36:57 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 18:04:18 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;
extern t_list		*g_proclist;
extern pid_t		g_pgid;

t_job		*ft_add_job(int status, char *cmd)
{
	t_job	new;
	t_list	*new_front;

	ft_dprintf(2, "ft_add_job");
	if (!g_proclist || (cmd && !(new.cmd = ft_strdup(cmd))))
		return (NULL);
	new.pgid = g_pgid;
	new.nbr = (g_jcont.job_nbr)++;
	new.status = status | RUNNING;
	new.process = g_proclist;
	g_proclist = NULL;
	ft_dprintf(2, ">>> job pgid: %i <<<\n", new.pgid);
	g_pgid = 0;
	if (!(new_front = ft_lstnew(&new, sizeof(t_job))))
	{
		free(new.cmd);
		return (NULL);
	}
	ft_lstadd(&(g_jcont.jobs), new_front);
	ft_set_prio();
	ft_dprintf(2, "ft_add_job_job_create");
	return (new_front->content);
}
