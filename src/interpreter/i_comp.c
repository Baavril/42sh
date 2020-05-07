/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:40:10 by bprunevi          #+#    #+#             */
/*   Updated: 2020/04/15 17:19:39 by petitfish        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "jcont.h"

int						g_mode;
extern int				g_retval;
int						g_compvalue;
extern int				g_fd[3];
extern int				g_fclose;

int				i_comp_list(t_elem left, t_elem right)
{
	expand_tree(left.v, 0);
	if (!(g_mode & FORK_SHELL))
		g_mode = FOREGROUND;
	g_compvalue = 0;
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
	expand_tree(left.v, 0);
	g_mode = BACKGROUND;
	g_compvalue = 0;
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
	if (!g_compvalue)
	{
		left.v->f(left.v->left, left.v->right);
		ft_launch_job();
	}
	if (!g_retval)
	{
		g_compvalue = 0;
		right.v->f(right.v->left, right.v->right);
	}
	else if (right.v->f == i_or_op || right.v->f == i_and_op)
	{
		g_compvalue = 1;
		right.v->f(right.v->left, right.v->right);
	}
	return (0);
}

int				i_or_op(t_elem left, t_elem right)
{
	if (!g_compvalue)
	{
		left.v->f(left.v->left, left.v->right);
		ft_launch_job();
	}
	if (g_retval)
	{
		g_compvalue = 0;
		right.v->f(right.v->left, right.v->right);
	}
	else if (right.v->f == i_or_op || right.v->f == i_and_op)
	{
		g_compvalue = 1;
		right.v->f(right.v->left, right.v->right);
	}
	return (0);
}
