/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 08:40:59 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/19 19:39:35 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "expansions.h"
#include "builtins.h"
#include "jcont.h"

int 			curjob_cat(char *str)
{
	extern t_job g_curjob;
	char *tmp;

	tmp = g_curjob.cmd;
	if (!g_curjob.cmd)
		g_curjob.cmd = ft_strdup(str);
	else
	{
		g_curjob.cmd = ft_strnjoin(3, g_curjob.cmd, " ", str);
		free(tmp);
	}
	ft_printf("%s\n", g_curjob.cmd);
	return (0);
}

int				shape(t_node *node)
{
	if (node->f == i_less
	||  node->f == i_dless
	||  node->f == i_lessand
	||  node->f == i_great
	||  node->f == i_dgreat
	||  node->f == i_greatand
	||  node->f == i_lessgreat
	||  node->f == i_dlessdash
	||  node->f == i_clobber)
		return(0b11);
	if (node->f == i_prefix
	||  node->f == i_suffix_word
	||  node->f == i_builtin
	||  node->f == i_exec)
		return(0b10);
	else
		return(0b00);
}

int				astdel(t_node *node)
{
	int node_type;

	if (!node)
		return(1);
	node_type = shape(node);
	if (node->left.c || node->left.v)
	{
		if (node_type & 0b10)
		{
			//ft_printf("free left [%p]\n", node->left.c);
			//ft_printf("free left [%s]\n", node->left.c);
			free(node->left.c);
		}
		else
			astdel(node->left.v);
		node->left.c = NULL;
	}
	if (node->right.c || node->right.v)
	{
		if (node_type & 0b01)
		{
			//ft_printf("free left [%p]\n", node->right.c);
			//ft_printf("free left [%s]\n", node->right.c);
			free(node->right.c);
		}
		else
			astdel(node->right.v);
		node->right.c = NULL;
	}
	free(node);
	return (0);
}

int				expand_tree(t_node *node)
{
	int node_type;

	if (!node)
		return(1);
	node_type = shape(node);
	if (node->left.c || node->left.v)
	{
		if (node_type & 0b10)
		{
			curjob_cat(node->left.c);
			expansions_treatment(&(node->left.c));
		}
		else
			expand_tree(node->left.v);
	}
	if (node->f == i_pipe_sequence)
		curjob_cat("|" );
	if (node->right.c || node->right.v)
	{
		if (node_type & 0b01)
		{
			curjob_cat(node->right.c);
			expansions_treatment(&(node->right.c));
		}
		else
			expand_tree(node->right.v);
	}
	if (node->f == i_exec)
		if (is_a_builtin(node->left.c) || eval_command(&node->left.c))
			node->f = i_builtin;
	return (0);
}
