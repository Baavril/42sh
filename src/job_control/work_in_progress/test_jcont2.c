/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 08:46:44 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/11 21:05:32 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <stdint.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <signal.h>
#include <string.h>

#include "jcont.h"

extern int		errno;
extern char		**environ;

void	exec_test1(int std_fd[3])// exec yes
{
	char		*argv[2] = {"ls", NULL};

	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);
	if (std_fd[0] != STDIN_FILENO)
	{
		dup2(std_fd[0], STDIN_FILENO);
		close(std_fd[0]);
	}
	if (std_fd[1] != STDOUT_FILENO)
	{
		dup2(std_fd[1], STDOUT_FILENO);
		close(std_fd[1]);
	}
	execve("/usr/bin/yes", argv, environ); //print en boucle argv[1]
}

void	exec_test2(int std_fd[3]) //exec nl
{
	char		*argv[2] = {"nl", NULL};

	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);
	argv[1] = NULL;
	if (std_fd[0] != STDIN_FILENO)
	{
		dup2(std_fd[0], STDIN_FILENO);
		close(std_fd[0]);
	}
	if (std_fd[1] != STDOUT_FILENO)
	{
		dup2(std_fd[1], STDOUT_FILENO);
		close(std_fd[1]);
	}
	execve("/usr/bin/nl", argv, environ);
}

void		ft_sigchld_handler(int nbr)
{
	int			ret_status;
	int			pid;

	dprintf(2, "\nSIGCHLD recu !!!\n");
	while ((pid = waitpid(WAIT_ANY, &ret_status, WUNTRACED | WNOHANG)) > 0) // on demande au kernel de nous parler de tous les process en attente
	{
		dprintf(2, "Found this pid after wait in Handler: %i\nReturnCode:%i\n", pid, ret_status); //infos sur les process enfants recuperes
		if ((WIFSTOPPED(ret_status)))
			dprintf(2, "was stopped: STOPNBR: %i\n", WSTOPSIG(ret_status));
		if ((WIFSIGNALED(ret_status)))
			dprintf(2, "was signaled: SIGNBR: %i\n", WTERMSIG(ret_status));
		if ((WIFEXITED(ret_status)))
			dprintf(2, "has exited: status: %i\n", WEXITSTATUS(ret_status));
	}
	dprintf(2, "NO MORE WAIT VALUE\n\n");
	return ;
}

int main(int argc, char **argv)
{
	int i;
	int j;
	int rtn_value;
	int shell_term;
	char line[100];
	int std_fd1[3];
	int pipe1_fd[2];
	int std_fd2[3];
	int pipe2_fd[2];
	int std_fd3[3];

	// Mise en place des pipes: ici, c'est degeux parce que je close jamais rien.
	std_fd1[0] = STDIN_FILENO;
	std_fd3[1] = STDOUT_FILENO;
	std_fd1[2] = STDERR_FILENO;
	std_fd2[2] = STDERR_FILENO;
	std_fd3[2] = STDERR_FILENO;
	pipe(pipe2_fd);
	std_fd2[1] = pipe2_fd[1];
	std_fd3[0] = pipe2_fd[0];
	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);
	signal (SIGTTIN, SIG_IGN);
	signal (SIGTTOU, SIG_IGN);
	signal (SIGCHLD, ft_sigchld_handler); // On ecoute les enfants
	shell_term = STDIN_FILENO;
	dprintf(2, "return of attempt at putting self in fg: %i\n", j = tcsetpgrp(shell_term, getpgrp())); //mise en avant du shell group dans le terminal
	int			to_close[2] = {pipe2_fd[1], -1};
	ft_add_process(&exec_test2, std_fd3, to_close);
	pipe(pipe1_fd);
	std_fd1[1] = pipe1_fd[1];
	std_fd2[0] = pipe1_fd[0];
	to_close[0] = pipe1_fd[1];
	to_close[1] = pipe2_fd[0];
	ft_add_process(&exec_test2, std_fd2, to_close);
	close(pipe2_fd[0]);
	close(pipe2_fd[1]);
	to_close[0] = pipe1_fd[0];
	to_close[1] = -1;
	ft_add_process(&exec_test1, std_fd1, to_close);
	close(pipe1_fd[0]);
	close(pipe1_fd[1]);
	ft_putendl("Avant job");
	ft_launch_job(ft_strdup("plop"), FOREGROUND);
	ft_putendl("Apres job");
	while (1) //boucle debile pour faire tourner le pere: pas de wait => groupe en background
		ft_putendl("Apres job");
}
