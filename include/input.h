/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:11:17 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/03 11:07:42 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define COUNT_KEY	 8
# define CTRL_L		12
# define CTRL_R		18
# define ESC		'\033'
# define INPUT_SIZE	256

char				*copybuff;
char				*inside_history;

union				u_tc
{
	char			key;
	char			buff[COUNT_KEY];
};

typedef struct		s_cursor
{
	size_t			in;
	size_t			end;
	size_t			start;
	size_t			prompt_len;
	size_t			match_ret;
	size_t			on;
	size_t			ctrl_r;
	char			*prompt;
	char			*match;
}					t_cursor;

typedef struct		s_dispatch_keys
{
	char			*key_path;
	int				(*function_call)(char**, t_cursor*);
}					t_dispatch_keys;

int					read_command(char **line);
int					toggle_termcaps(void);
void				restore_term_mode();
int					get_stdin(t_cursor *cursor, char **buff);
int					search_analyzer(union u_tc *term, char **buff, t_cursor *cursor);
int					standard_analyzer(union u_tc *term, char **buff, t_cursor *cursor);
void				ft_reader(union u_tc *term, t_cursor *cursor, char ***buff);
void				ft_init_cursor(t_cursor *cursor);

int					keyboard_dispatcher(union u_tc *term, char **buff, t_cursor *cursor);
int					keyboard_ctrl_l(union u_tc *term, char **buff, t_cursor *cursor);
int					keyboard_normal_char(union u_tc *term, char **buff, t_cursor *cursor);
int					keyboard_backspace(union u_tc *term, char **buff, t_cursor *cursor);
int					keyboard_tabulation(union u_tc *term, char **buff, t_cursor *cursor);

int					set_reader(union u_tc *term, char **buff, t_cursor *cursor);

int					keyboard_enter(union u_tc *term,char **buff, t_cursor *cursor);
void				update_buff(char **buff, t_cursor *cursor);
int					ft_init_tab(void);


#endif
