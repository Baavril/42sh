/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigchld_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:50:48 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/07 15:27:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;

void		ft_sigchld_handler(int nbr)
{
	int			ret_status;
	int			pgid;
	t_list		*voyager;
	t_job		*job;

	if (!(voyager = g_jcont.jobs)
	|| (pgid = waitpid(WAIT_ANY, &ret_status, WUNTRACED | WNOHANG)) < 0)
		return ;
	while ((voyager))
	{
		job = voyager->content;
		if (job->pgid == pgid
		&& ISBACKGROUND(job->status) && killpg(job->pgid, 0) == -1)
			job->status = ret_status | BACKGROUND;
		voyager = voyager->next;
	}
}
