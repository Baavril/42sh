/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:11:17 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/22 16:11:55 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stddef.h>

# define COUNT_KEY	8
# define CTRL_A		0x01
# define CTRL_B		0x02
# define CTRL_C		0x03
# define CTRL_D		0x04
# define CTRL_E		0x05
# define CTRL_F		0x06
# define CTRL_G		0x07
# define CTRL_H		0x08
# define CTRL_I		0x09
# define CTRL_J		0x0a
# define CTRL_K		0x0b
# define CTRL_L		0x0c
# define CTRL_M		0x0d
# define CTRL_N		0x0e
# define CTRL_O		0x0f
# define CTRL_P		0x10
# define CTRL_Q		0x11
# define CTRL_R		0x12
# define CTRL_S		0x13
# define CTRL_T		0x14
# define CTRL_U		0x15
# define CTRL_V		0x16
# define CTRL_W		0x17
# define CTRL_X		0x18
# define CTRL_Y		0x19
# define CTRL_Z		0x1a
# define ESC		'\033'
# define INPUT_SIZE	256

# define STD_INPUT		1
# define QUOTE_INPUT	2

char				*g_copybuff;
char				*g_inside_history;

union				u_tc
{
	char			key;
	char			buff[COUNT_KEY + 1];
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
int					search_analyzer(union u_tc *term, char **buff,
															t_cursor *cursor);
int					standard_analyzer(union u_tc *term, char **buff,
															t_cursor *cursor);
int					analyzer(t_cursor *cursor, char **buff, union u_tc *term);
void				ft_reader(union u_tc *term, t_cursor *cursor, char ***buff);
void				ft_init_cursor(t_cursor *cursor);

int					keyboard_dispatcher(union u_tc *term, char **buff,
															t_cursor *cursor);
int					keyboard_ctrl_c(union u_tc *term, char **buff,
															t_cursor *cursor);
int					keyboard_ctrl_d(union u_tc *term, char **buff,
															t_cursor *cursor);
int					keyboard_ctrl_search(union u_tc *term, char **buff,
															t_cursor *cursor);
int					keyboard_ctrl_l(union u_tc *term, char **buff,
															t_cursor *cursor);
int					keyboard_normal_char(union u_tc *term, char **buff,
															t_cursor *cursor);
int					keyboard_backspace(union u_tc *term, char **buff,
															t_cursor *cursor);
int					keyboard_tabulation(union u_tc *term, char **buff,
															t_cursor *cursor);

int					set_reader(union u_tc *term, char **buff, t_cursor *cursor);

int					keyboard_enter(union u_tc *term, char **buff,
															t_cursor *cursor);
void				update_buff(char **buff, t_cursor *cursor);
int					init_key_tab(void);

#endif
