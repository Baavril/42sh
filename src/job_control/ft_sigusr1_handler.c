/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigusr1_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:32:04 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/02 15:07:52 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "jcont.h"

void		ft_sigusr1_handler(int nbr, siginfo_t *siginfo, void *context)
{
#include <unistd.h>
	extern t_job		g_curjob;
	t_process			*process;

	write(2, "SIGUSR1 handler: START\n", 23);
	write(2, ft_itoa(siginfo->si_pid), 6);
	write(2, "\n", 1);
	(void)nbr;
	(void)context;
	if (!(process = ft_get_process_pid(siginfo->si_pid)))
	{
		write(2, "SIGUSR1 handler: PROBLEM\n", 25);
		return ;
	}
	process->ready = READY;
	write(2, "SIGUSR1 handler: END\n", 21);
}

void			ft_catch_sigusr1(int nbr)
{
	(void)nbr;
}
