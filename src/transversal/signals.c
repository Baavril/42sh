/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:47:47 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 22:50:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "sig_handler.h"

void			set_signals(void)
{
	struct sigaction	action;

	signal(SIGCHLD, &ft_sigchld_handler);
	ft_bzero(&action, sizeof(sigaction));
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &ft_sigusr1_handler;
	sigaction(SIGUSR1, &action, NULL);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
