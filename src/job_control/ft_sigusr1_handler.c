/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigusr1_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:32:04 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 22:43:00 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "jcont.h"

void		ft_sigusr1_handler(int nbr, siginfo_t *siginfo, void *context)
{
	extern t_jcont		g_jcont;
	extern t_job		g_curjob;
	t_process			*process;

	(void)nbr;
	(void)context;
	if (!(process = ft_get_process_pid(siginfo->si_pid))
	&& !(process = ft_get_process_from_job(&g_curjob, siginfo->si_pid)))
		return ;
	process->ready = 1;
}

void			ft_catch_sigusr1(int nbr)
{
	(void)nbr;
}
