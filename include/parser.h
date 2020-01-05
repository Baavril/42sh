/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:02:57 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/05 09:34:24 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

#include "tokens.h"
#include <fcntl.h>
#define CREATE_RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

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
int i_execnode(t_elem left, t_elem right);
int i_builtin(t_elem left, t_elem right);
int i_prefix(t_elem left, t_elem right);
int i_add_process(t_elem left, t_elem right);
int i_exec(t_elem left, t_elem right);
int i_suffix_word(t_elem left, t_elem right);
int i_suffix_redirect(t_elem left, t_elem right);
int i_debugredirect(t_elem left, t_elem right);

int	i_less(t_elem left, t_elem right);
int	i_dless(t_elem left, t_elem right);
int	i_lessand(t_elem left, t_elem right);
int	i_great(t_elem left, t_elem right);
int	i_dgreat(t_elem left, t_elem right);
int	i_greatand(t_elem left, t_elem right);
int	i_lessgreat(t_elem left, t_elem right);
int	i_dlessdash(t_elem left, t_elem right);
int	i_clobber(t_elem left, t_elem right);

int is_regfile(const char *arg);
int eval_command(char **arg);
int val_command(char **arg);
int	open_on_fd(const char *path, int o_flags, mode_t mode, int final_fd);
int	free_ast(t_node *node);
#endif
