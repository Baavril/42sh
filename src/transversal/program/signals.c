/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:47:47 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/17 19:29:09 by tgouedar         ###   ########.fr       */
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
	{SIGHUP, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGINT, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGQUIT, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGILL, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGTRAP, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGABRT, {SIG_DFL, SIG_DFL, &ft_transferkill}},
	{SIGFPE, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGBUS, {SIG_DFL, SIG_DFL, &ft_transferkill}},
	{SIGSEGV, {SIG_DFL, SIG_DFL, &ft_transferkill}},
	{SIGSYS, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGPIPE, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGALRM, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGTERM, {SIG_IGN, SIG_DFL, &ft_transferkill}},
	{SIGURG, {SIG_IGN, SIG_DFL, SIG_IGN}},
	{SIGTSTP, {SIG_IGN, SIG_DFL, &ft_transferstop}},
	{SIGCONT, {SIG_IGN, SIG_DFL, &ft_transfercont}},
	{SIGCHLD, {&ft_sigchld_handler, SIG_DFL, &ft_sigchld_handler}},
	{SIGTTIN, {SIG_IGN, SIG_DFL, SIG_IGN}},
	{SIGTTOU, {SIG_IGN, SIG_DFL, SIG_IGN}},
	{SIGXFSZ, {SIG_IGN, SIG_DFL, &ft_transfersig}},
	{SIGVTALRM, {SIG_IGN, SIG_DFL, &ft_transfersig}},
	{SIGPROF, {SIG_IGN, SIG_DFL, &ft_transfersig}},
	{SIGUSR1, {SIG_IGN, SIG_IGN, SIG_IGN}},
	{SIGUSR2, {SIG_IGN, SIG_IGN, SIG_IGN}},
	{0, {NULL, NULL}},
};

void			set_signals(int id)
{
	struct sigaction	action;
	int					i;
	t_sig				*signal;

	i = 1;
	signal = &(g_sigdispatcher[i]);
	while ((signal->sig_nbr))
	{
		ft_bzero(&action, sizeof(action));
		sigemptyset(&action.sa_mask);
		action.sa_handler = signal->handlers[id];
		sigaction(signal->sig_nbr, &action, NULL);
		signal = &(g_sigdispatcher[++i]);
	}
}
