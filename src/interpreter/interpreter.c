/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:13:59 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/07 14:28:54 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <unistd.h>
char **argv;

int i_comp_list(t_elem left, t_elem right)
{
	int i;
	int rtn_value;
	if (!(i = fork()))
		left.v->f(left.v->left, left.v->right);
	waitpid(i, &rtn_value, WUNTRACED);
	if (!(i = fork()))
		right.v->f(right.v->left, right.v->right);
	waitpid(i, &rtn_value, WUNTRACED);
	ft_printf("command returned %d\n", rtn_value);
	return (rtn_value);
}
int i_pipe_sequence(t_elem left, t_elem right)
{
	int pipe_fd[2];

	pipe(pipe_fd);
	if (!fork())
	{
		ft_printf("Started prog_1 with {%d;%d}\n", pipe_fd[0], pipe_fd[1]);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		left.v->f(left.v->left, left.v->right);
	}
	else
	{
		ft_printf("Started prog_2 with {%d;%d}\n", pipe_fd[0], pipe_fd[1]);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		right.v->f(right.v->left, right.v->right);
	}
	return(-1);
}
int i_simple_command(t_elem left, t_elem right)
{
	(void) left;
	(void) right;
	left.v->f(left.v->left, left.v->right);
	right.v->f(right.v->left, right.v->right);
	return(0);
}
int i_prefix(t_elem left, t_elem right)
{
	(void) left;
	(void) right;
	extern char **environ;
	while (*environ + 1)
		environ++;
	*environ = ft_strdup("SALUT=SALUT");
	return(0);
}

int i_exec(t_elem left, t_elem right)
{
	(void) left;
	(void) right;
	extern char **environ;
	argv = malloc(sizeof(char *) * 3);
	argv[0] = left.c;
	argv[1] = NULL;
	//right.v->f(right.v->left, right.v->right);
	execve(argv[0], argv, environ);
	return(-1);
}
int i_suffix(t_elem left, t_elem right)
{
	(void) left;
	(void) right;
	int i;
	i = 0;
	while (argv[++i])
		(void) i;
	argv[i] = left.c;
	argv[++i] = NULL;
	return(0);
}
int i_debugredirect(t_elem left, t_elem right)
{
	(void) left;
	(void) right;
	ft_printf("REDIRECT");
	return(0);
}
