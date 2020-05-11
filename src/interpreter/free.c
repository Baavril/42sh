/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 08:40:59 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/10 15:11:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "expansions.h"
#include "termcaps.h"
#include "builtins.h"
#include "curjob.h"
#include "prompt.h"
#include "parser.h"
#include "input.h"
#include "libft.h"

int					shape(t_node *node)
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
		return (0b110);
	if (node->f == i_prefix
	|| node->f == i_suffix_word
	|| node->f == i_builtin
	|| node->f == i_exec)
		return (0b100);
	else
		return (0b000);
}

int					astdel(t_node *node)
{
	int node_type;

	if (!node)
		return (1);
	node_type = shape(node);
	if (node->left.c || node->left.v)
	{
		if (node_type & 0b100)
			free(node->left.c);
		else
			astdel(node->left.v);
		node->left.c = NULL;
	}
	if (node->right.c || node->right.v)
	{
		if (node_type & 0b010)
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
	char		*name;
	char		*line;
	char		*buff;
	t_cursor	cursor;

	name = ft_strjoinfree(*area, ft_strdup("\n"));
	*area = ft_strdup("");
	set_termcaps(TC_INPUT);
	while (!line || (ft_strcmp(line, name) && !(line = NULL)))
	{
		*area = ft_strjoinfree(*area, line);
		while (!line || line[ft_strlen(line) - 1] != '\n')
		{
			ft_init_cursor(&cursor);
			mkprompt_quote("\'", &(cursor.prompt), &(cursor.prompt_len));
			get_stdin(&cursor, &buff);
			buff = ft_strjoinfree(buff, ft_strdup("\n"));
			expansions_treatment(&buff, 1);
			line = ft_strjoinfree(line, buff);
			write(1, "\n", 1);
		}
	}
	ft_strdel(&name);
	ft_strdel(&line);
	set_termcaps(TC_RESTORE);
}

static void			expand_tree_function(t_node *node, int data)
{
	if (node->f == i_exec)
	{
		if (is_a_builtin(node->left.c))
		{
			if (!data)
				node->f = i_builtin;
		}
		else if (eval_command(&node->left.c))
			node->f = i_builtin;
	}
}

void				expand_tree(t_node *node, int data)
{
	if (!node)
		return ;
	data = shape(node) | (data & 0b001) | (node->f == i_pipe_sequence);
	if (node->left.c || node->left.v)
	{
		if ((data & 0b100) && !(curjob_cat(node->left.c)))
			expansions_treatment(&(node->left.c), 0);
		else
			expand_tree(node->left.v, data);
	}
	curjob_add(node);
	if (node->right.c || node->right.v)
	{
		if ((data & 0b010) && !(curjob_cat(node->right.c)))
		{
			expansions_treatment(&(node->right.c), 0);
			if (node->f == i_dless)
				process_heredoc(&(node->right.c));
		}
		else
			expand_tree(node->right.v, data);
	}
	expand_tree_function(node, data);
}
