/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_jcont.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:24:58 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/28 17:02:15 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

extern t_jcont		g_jcont;

int			ft_a_stopped_job(void)
{
	t_list		*voyager;

	voyager = g_jcont.jobs;
	while (voyager)
	{
		if (WIFSTOPPED(((t_job*)(voyager->content))->status))
			return (1);
		voyager = voyager->next;
	}
	return (0);
}

int			ft_free_jcont(int flag)
{
	if (flag == STOP_CHECK && ft_a_stopped_job())
		return (1);
	ft_lstdel(&(g_jcont.jobs), &ft_free_job);
	return (0);
}
