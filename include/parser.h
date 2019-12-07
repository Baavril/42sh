/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:02:57 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/03 19:07:46 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

#include "tokens.h"

typedef union	elem
{
	char *c;
	struct s_node *v;
}		t_elem;

typedef	struct	s_node
{
	t_elem	left;
	t_elem	right;
	int		(*f)(t_elem, t_elem);
}				t_node;

//parser.c
void	parser_21sh(char *input);
//is_potential.c
int		is_potential(t_token tok, int i);
//io_redirect.c
t_node	*io_redirect(t_token tok);
//pipe_sequence.c
t_node	*and_or(t_token tok);
//simple_command.c
t_node	*command(t_token tok);
//terminals.c
char	*word(t_token tok);
char	*assig_word(t_token tok);
char	*io_number(t_token tok);
//wordtypes.c
char	*filename(t_token tok);
char	*here_end(t_token tok);
char	*cmd_name(t_token tok);
char	*cmd_word(t_token tok);
//debug_gnt.c
t_token	gnt(char *future);
t_token	peek(void);
//debug_interpreter.c
void	debug_parser(char *input);

int i_comp_list(t_elem left, t_elem right);
int i_pipe_sequence(t_elem left, t_elem right);
int i_simple_command(t_elem left, t_elem right);
int i_prefix(t_elem left, t_elem right);
int i_exec(t_elem left, t_elem right);
int i_suffix(t_elem left, t_elem right);
int i_debugredirect(t_elem left, t_elem right);

#endif
