/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:13:59 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/14 16:39:37 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sys/wait.h"
#include "parser.h"
#include "shell_variables.h"
#include "builtins.h"
#include <unistd.h>
#include "builtins.h"
#include "error.h"
#include "jcont.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

char **g_argv;
int g_fd[3] = {STDIN, STDOUT, STDERR};
int g_fclose = -1;

int i_comp_list(t_elem left, t_elem right)
{
	left.v->f(left.v->left, left.v->right);
	ft_launch_job("plop", FOREGROUND);
	right.v->f(right.v->left, right.v->right);
	return (0);
}

int i_pipe_sequence(t_elem left, t_elem right)
{
	int pipe_fd[2];
	int bckp;

	pipe(pipe_fd);
	ft_printf("Create pipe with {%d->%d}\n", pipe_fd[0], pipe_fd[1]);
	//0, 1, 2 | -1 -1 -1
	bckp = g_fd[1];
	g_fd[1] = pipe_fd[1];
	g_fclose = pipe_fd[0];
	left.v->f(left.v->left, left.v->right);// 0, P0, 2 | P1 -1 -1
	g_fd[1] = bckp;
	g_fd[0] = pipe_fd[0];
	ft_printf("pipe_seq closing {%d}\n", pipe_fd[1]);
	close(pipe_fd[1]);
	g_fclose = -1;
	right.v->f(right.v->left, right.v->right);// P1, 1, 2 | -1 -1 -1
	close(pipe_fd[1]);
	return(-1);
}

int i_prefix(t_elem left, t_elem right)
{
	/* comment parcourir tout l'arbre et recuperer les donnees ? */
	listadd_back(newnodshell(left.c, 0));
	cmd_set(0, NULL);
	/* reponse : comme ceci :D */
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return(0);
}

int i_exec(t_elem left, t_elem right)
{
	extern char **environ;
	g_argv = malloc(sizeof(char *) * 16); //NON
	g_argv[0] = left.c;
	g_argv[1] = NULL;
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	if (builtins_dispatcher(g_argv) == e_command_not_found)
		execve(g_argv[0], g_argv, environ);
	return(-1);
}

int i_execnode(t_elem left, t_elem right)
{
	if (left.v)
		left.v->f(left.v->left, left.v->right);
	right.v->f(right.v->left, right.v->right);
	return(0);
}

int i_simple_command(t_elem left, t_elem right)
{
	t_node execnode;
	execnode.left = left;
	execnode.right = right;
	execnode.f = i_execnode;
	ft_add_process(execnode, g_fd, g_fclose);
	return(0);
}

int i_suffix(t_elem left, t_elem right)
{
	int i;
	i = 0;
	while (g_argv[++i])
		(void) i;
	g_argv[i] = left.c;
	g_argv[++i] = NULL;
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return(0);
}

int i_debugredirect(t_elem left, t_elem right)
{
	(void) left;
	(void) right;
	ft_printf("REDIRECT");
	return(0);
}
