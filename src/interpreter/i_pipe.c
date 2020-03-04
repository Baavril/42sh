/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:42:04 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 13:48:02 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int						g_fd[3] = {STDIN, STDOUT, STDERR};
int						g_fclose = -1;

int				i_pipe_sequence(t_elem left, t_elem right)
{
	int pipe_fd[2];
	int bckp;

	pipe(pipe_fd);
	bckp = g_fd[1];
	g_fd[1] = pipe_fd[1];
	g_fclose = pipe_fd[0];
	left.v->f(left.v->left, left.v->right);
	g_fd[1] = bckp;
	g_fd[0] = pipe_fd[0];
	close(pipe_fd[1]);
	g_fclose = -1;
	bckp = right.v->f(right.v->left, right.v->right);
	close(pipe_fd[0]);
	return (bckp);
}
