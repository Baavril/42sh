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

# define INPUT_SIZE 256
# define MAX_LINE 4096

char *copybuff;
char *inside_history;

int	read_command(char **line);

union	u_tc
{
	char		key;
	char		buff[8];
};

typedef struct	s_cursor
{
	size_t	in;
	size_t	end;
	size_t	start;
	int		prompt_len;
	char	*prompt;
}				t_cursor;

typedef	struct s_dispatch_keys
{
	char	*key_path;
	void	(*function_call)(char**, t_cursor*);
}		t_dispatch_keys;

#endif
