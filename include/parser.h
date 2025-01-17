/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:02:57 by bprunevi          #+#    #+#             */
/*   Updated: 2020/07/17 15:09:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokens.h"
# include <fcntl.h>

# define TAB_SIZE 16

typedef union	u_elem
{
	char			*c;
	struct s_node	*v;
}				t_elem;

typedef struct	s_node
{
	t_elem		left;
	t_elem		right;
	int			(*f)(t_elem, t_elem);
}				t_node;

int				g_parsingerr;
void			execute(char *input);
int				is_potenti(t_token tok, int i);
t_node			*io_redirect(t_token tok);
t_node			*comp_list(t_token tok);
t_node			*command(t_token tok);
char			*word(t_token tok);
char			*assig_word(t_token tok);
char			*io_number(t_token tok);
char			*filename(t_token tok);
char			*here_end(t_token tok);
char			*cmd_name(t_token tok);
char			*cmd_word(t_token tok);
t_token			gnt(char *input, int future);

int				i_comp_list(t_elem left, t_elem right);
int				i_and_list(t_elem left, t_elem right);
int				i_pipe_sequence(t_elem left, t_elem right);
int				i_simple_command(t_elem left, t_elem right);
int				i_execnode(t_elem left, t_elem right);
int				i_builtin(t_elem left, t_elem right);
int				i_prefix(t_elem left, t_elem right);
int				i_add_process(t_elem left, t_elem right);
int				i_exec(t_elem left, t_elem right);
int				i_suffix_word(t_elem left, t_elem right);
int				i_redirect(t_elem left, t_elem right);
int				i_debugredirect(t_elem left, t_elem right);

int				i_less(t_elem left, t_elem right);
int				i_dless(t_elem left, t_elem right);
int				i_lessand(t_elem left, t_elem right);
int				i_great(t_elem left, t_elem right);
int				i_dgreat(t_elem left, t_elem right);
int				i_greatand(t_elem left, t_elem right);
int				i_lessgreat(t_elem left, t_elem right);
int				i_dlessdash(t_elem left, t_elem right);
int				i_clobber(t_elem left, t_elem right);
int				i_andgreat(t_elem left, t_elem right);
int				i_and_op(t_elem left, t_elem right);
int				i_or_op(t_elem left, t_elem right);

int				is_regfile(const char *arg);
int				is_dir(const char *arg);
int				eval_command(char **arg);
int				val_command(char **arg);
int				open_on_fd(const char *path, int o_flags, mode_t mode,
																int final_fd);
int				shape(t_node *node);
int				astdel(t_node *node);
int				expand_tree(t_node *node, int fork_builtin);
int				expand_args(t_node *node);

#endif
