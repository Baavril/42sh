/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:40:10 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/07 14:03:11 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "jcont.h"

int						g_mode;
extern int				g_retval;
extern int				g_fd[3];
extern int				g_fclose;

int				i_comp_list(t_elem left, t_elem right)
{
	expand_tree(left.v);
	if (!(g_mode & FORK_SHELL))
		g_mode = FOREGROUND;
	left.v->f(left.v->left, left.v->right);
	ft_launch_job();
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (0);
}

int				i_and_list(t_elem left, t_elem right)
{
	t_elem		empty;

	empty.v = NULL;
	expand_tree(left.v);
	g_mode = BACKGROUND;
	if (left.v->f == i_and_op || left.v->f == i_or_op)
	{
		g_mode |= FORK_SHELL;
		ft_add_process(empty, left, g_fd, g_fclose);
		g_mode ^= FORK_SHELL;
	}
	else
		left.v->f(left.v->left, left.v->right);
	ft_launch_job();
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (0);
}

int				i_and_op(t_elem left, t_elem right)
{
	expand_tree(left.v);
	left.v->f(left.v->left, left.v->right);
	ft_launch_job();
	if (!g_retval)
	{
		right.v->f(right.v->left, right.v->right);
		if (g_mode & FORK_SHELL)
			ft_launch_job();
	}
	return (0);
}

int				i_or_op(t_elem left, t_elem right)
{
	expand_tree(left.v);
	left.v->f(left.v->left, left.v->right);
	ft_launch_job();
	if (g_retval)
	{
		right.v->f(right.v->left, right.v->right);
		if (g_mode & FORK_SHELL)
			ft_launch_job();
	}
	return (0);
}
