/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:40:10 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 13:48:02 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "jcont.h"

int						g_mode;
extern int				g_retval;

int				i_comp_list(t_elem left, t_elem right)
{
	expand_tree(left.v);
	g_mode = FOREGROUND;
	left.v->f(left.v->left, left.v->right);
	ft_launch_job();
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (0);
}

int				i_and_list(t_elem left, t_elem right)
{
	expand_tree(left.v);
	g_mode = BACKGROUND;
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
	if (g_mode == FOREGROUND)
		ft_launch_job();
	if (!g_retval)
		right.v->f(right.v->left, right.v->right);
	return (0);
}

int				i_or_op(t_elem left, t_elem right)
{
	expand_tree(left.v);
	left.v->f(left.v->left, left.v->right);
	if (g_mode == FOREGROUND)
		ft_launch_job();
	if (g_retval)
		right.v->f(right.v->left, right.v->right);
	return (0);
}
