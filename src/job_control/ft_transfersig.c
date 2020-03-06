/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transfersig.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:39:09 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/06 13:17:58 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include "error.h"
#include "sig_handler.h"
#include <signal.h>

extern t_jcont		g_jcont;

void				ft_transferkill(int nbr)
{
	t_list		*voyager;
	t_job		*job;

	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = (t_job*)voyager->content;
		kill(-job->pgid, nbr);
		voyager = voyager->next;
	}
	ft_clean_exit(NULL, WHARD_EXIT | nbr);
}

void				ft_transferstop(int nbr)
{
	t_list		*voyager;
	t_job		*job;

	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = (t_job*)voyager->content;
		kill(-job->pgid, nbr);
		voyager = voyager->next;
	}
	ft_update_job_status();
	signal(nbr, SIG_DFL);
	kill(0, nbr);
}

void				ft_transfercont(int nbr)
{
	t_list		*voyager;
	t_job		*job;

	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = (t_job*)voyager->content;
		kill(-job->pgid, nbr);
		voyager = voyager->next;
	}
	ft_update_job_status();
}

void				ft_transfersig(int nbr)
{
	t_list		*voyager;
	t_job		*job;

	voyager = g_jcont.jobs;
	while (voyager)
	{
		job = (t_job*)voyager->content;
		kill(-job->pgid, nbr);
		voyager = voyager->next;
	}
	ft_update_job_status();
	signal(nbr, SIG_DFL);
	kill(0, nbr);
}
