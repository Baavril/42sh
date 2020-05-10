/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 08:40:59 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/08 15:58:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "expansions.h"
#include "builtins.h"
#include "curjob.h"
#include "prompt.h"
#include "input.h"
#include "termcaps.h"
#include <unistd.h>

int				shape(t_node *node)
{
	if (node->f == i_less
	|| node->f == i_dless
	|| node->f == i_lessand
	|| node->f == i_great
	|| node->f == i_dgreat
	|| node->f == i_greatand
	|| node->f == i_lessgreat
	|| node->f == i_dlessdash
	|| node->f == i_clobber
	|| node->f == i_andgreat)
		return (0b11);
	if (node->f == i_prefix
	|| node->f == i_suffix_word
	|| node->f == i_builtin
	|| node->f == i_exec)
		return (0b10);
	else
		return (0b00);
}

int				astdel(t_node *node)
{
	int node_type;

	if (!node)
		return (1);
	node_type = shape(node);
	if (node->left.c || node->left.v)
	{
		if (node_type & 0b10)
			free(node->left.c);
		else
			astdel(node->left.v);
		node->left.c = NULL;
	}
	if (node->right.c || node->right.v)
	{
		if (node_type & 0b01)
			free(node->right.c);
		else
			astdel(node->right.v);
		node->right.c = NULL;
	}
	free(node);
	return (0);
}

void				process_heredoc(char **area)
{
	char *name;
	char *line;
	t_cursor	cursor;

	name = ft_strjoinfree(*area, ft_strdup("\n"));
	*area = ft_strdup("");
	line = ft_strdup("");
	set_termcaps(TC_INPUT);
	while (!line || !name || ft_strcmp(line, name))
	{
		*area = ft_strjoinfree(*area, line);
		ft_init_cursor(&cursor);
		mkprompt_quote("\'", &(cursor.prompt), &(cursor.prompt_len));
		get_stdin(&cursor, &line);
		line = ft_strjoinfree(line, ft_strdup("\n"));
		expansions_treatment(&line, 1);
		write(1, "\n", 1);
	}
	set_termcaps(TC_RESTORE);
}	

int				expand_tree(t_node *node, int fork_builtin)
{
	int node_type;

	if (!node)
		return (1);
	node_type = shape(node);
	if (node->f == i_pipe_sequence)
	{
		ft_printf("pipe!\n");
		fork_builtin = 1;
	}
	if (node->left.c || node->left.v)
	{
		if ((node_type & 0b10) && !(curjob_cat(node->left.c)))
			expansions_treatment(&(node->left.c), 0);
		else
			expand_tree(node->left.v, fork_builtin);
	}
	curjob_add(node);
	if (node->right.c || node->right.v)
	{
		if ((node_type & 0b01) && !(curjob_cat(node->right.c)))
		{
			expansions_treatment(&(node->right.c), 0);
			if (node->f == i_dless)
				process_heredoc(&(node->right.c));
		}
		else
			expand_tree(node->right.v, fork_builtin);
	}
	if (node->f == i_exec)
	{
		if (is_a_builtin(node->left.c))
		{
			if (!fork_builtin)
				node->f = i_builtin;
		}
		else if (eval_command(&node->left.c))
			node->f = i_builtin;
	}
	return (0);
}
