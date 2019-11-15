/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:11:17 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/13 15:06:18 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define COUNT_KEY 8
# define CTRL_L 12
# define CLEAR "clear"
# define INPUT_SIZE 256
# define MAX_LINE 4096

char *copybuff;
char *inside_history;

int	read_command(char **line);

union	u_tc
{
	unsigned int key_c;
	char		key;
	char		buff[COUNT_KEY];
};

typedef struct	s_cursor
{
	size_t	in;
	size_t	end;
	size_t	start;
	size_t	prompt_len;
	size_t	search_prompt_len;
	char	*prompt;
	char	*search_prompt;
}				t_cursor;

typedef	struct s_dispatch_keys
{
	char	*key_path;
	int		(*function_call)(char**, t_cursor*);
}		t_dispatch_keys;

int	get_stdin(t_cursor cursor, char **buff);
void	ft_init_cursor(t_cursor *cursor);
void	ft_reader(union u_tc *termcaps, t_cursor *cursor, char ***buff);

#endif
