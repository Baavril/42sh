/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:47:47 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/02 13:04:07 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "sig_handler.h"

t_sig			g_sigdispatcher[] =
{
	{SIGHUP, {SIG_IGN, SIG_DFL}},
	{SIGINT, {SIG_IGN, SIG_DFL}},
	{SIGQUIT, {SIG_IGN, SIG_DFL}},
	{SIGILL, {SIG_IGN, SIG_DFL}},
	{SIGABRT, {SIG_IGN, SIG_DFL}},
	{SIGFPE, {SIG_IGN, SIG_DFL}},
	{SIGKILL, {SIG_IGN, SIG_DFL}},
	{SIGBUS, {SIG_IGN, SIG_DFL}},
	{SIGSEGV, {SIG_IGN, SIG_DFL}},
	{SIGSYS, {SIG_IGN, SIG_DFL}},
	{SIGPIPE, {SIG_IGN, SIG_DFL}},
	{SIGALRM, {SIG_IGN, SIG_DFL}},
	{SIGTERM, {SIG_IGN, SIG_DFL}},
	{SIGURG, {SIG_IGN, SIG_DFL}},
	{SIGSTOP, {SIG_IGN, SIG_DFL}},
	{SIGTSTP, {SIG_IGN, SIG_DFL}},
	{SIGCONT, {SIG_IGN, SIG_DFL}},
	{SIGCHLD, {&ft_sigchld_handler, SIG_DFL}},
	{SIGTTIN, {SIG_IGN, SIG_DFL}},
	{SIGTTOU, {SIG_IGN, SIG_DFL}},
	{SIGXFSZ, {SIG_IGN, SIG_DFL}},
	{SIGVTALRM, {SIG_IGN, SIG_DFL}},
	{SIGPROF, {SIG_IGN, SIG_DFL}},
//	{SIGWINCH, {SIG_IGN, SIG_DFL}},
//	{SIGINFO, {SIG_IGN, SIG_DFL}},
	{SIGUSR1, {(void*)(&ft_sigusr1_handler), &ft_catch_sigusr1}},
	{SIGUSR2, {SIG_IGN, SIG_DFL}},
	{0, {NULL, NULL}},
};



void			set_signals(int id)
{
	sigset_t			block_mask;
	struct sigaction	action;
	int					i;
	t_sig				*signal;

	i = 1;
	sigemptyset(&block_mask);
	signal = &(g_sigdispatcher[i]);
	while ((signal->sig_nbr))
	{
		ft_bzero(&action, sizeof(sigaction));
		if (id == FATHER && signal->sig_nbr == SIGCHLD)
		{
			action.sa_flags = SA_SIGINFO;
			action.sa_sigaction = (t_ft_sigact_handler)(signal->handlers[id]);
		}
		else
			action.sa_handler = signal->handlers[id];
		action.sa_mask = block_mask;
		sigaction(signal->sig_nbr, &action, NULL);
		signal = &(g_sigdispatcher[++i]);
	}
}
