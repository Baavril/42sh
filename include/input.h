/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:11:17 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/20 11:26:55 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define INPUT_SIZE 256
# define MAX_LINE 4096

char *copybuff;
char *inside_history;

int	read_command(char **line);

typedef struct	s_cursor
{
	size_t	in;
	size_t	end;
	size_t	start;
	int		prompt_len;
	char	*prompt;
}				t_cursor;

#endif
