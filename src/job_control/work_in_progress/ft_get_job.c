/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:13:51 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/10 13:16:42 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;

int					ft_get_nbr_pgid(int nbr)
{
	t_list	*voyager;

	if (!(voyager = g_jcont.jobs))
		return (-1);
	if (nbr < 1)
		nbr = g_jcont.active_jobs[0];
	if (nbr >= g_jcont.job_nbr)
		return (-1);
	while ((voyager) && ((t_job*)(voyager->content))->nbr != nbr)
		voyager = voyager->next;
	if (!voyager)
		return (-1);
	return (((t_job*)(voyager->content))->pgid);
}

t_job				*ft_get_job_pgid(pid_t pgid)
{
	t_list	*voyager;

	if (!(voyager = g_jcont.jobs))
		return (NULL);
	while ((voyager) && ((t_job*)(voyager->content))->pgid != pgid)
		voyager = voyager->next;
	if (!voyager)
		return (NULL);
	return ((t_job*)(voyager->content));
}

t_job				*ft_get_job_nbr(int job_nbr)
{
	t_list	*voyager;

	if (!(voyager = g_jcont.jobs))
		return (NULL);
	while ((voyager) && ((t_job*)(voyager->content))->nbr != job_nbr)
		voyager = voyager->next;
	if (!voyager)
		return (NULL);
	return ((t_job*)(voyager->content));
}
