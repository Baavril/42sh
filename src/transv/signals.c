/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:56:23 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 18:56:42 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "sig_handler.h"
#include "job.h"

void	kill_child(int sig)
{
	extern pid_t	g_childpid;

	(void)sig;
	if (g_childpid)
	{
		kill(g_childpid, SIGKILL);
		g_childpid = 0;
		write(STDOUT_FILENO, "\n", sizeof(char));
	}
}

int	set_signals(int type)
{
	if (!type)
	{
		if ((signal(SIGINT, SIG_IGN) == SIG_ERR))
			exit(2);
	}
	else
	{
		if ((signal(SIGINT, kill_child) == SIG_ERR))
			exit(2);
	}
	return (0);
}
