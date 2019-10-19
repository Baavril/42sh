/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:11:17 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/19 15:00:23 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define INPUT_SIZE 256
# define PROMPT_CHARS " 21sh > "

typedef struct 	s_posinfo
{
	int fd;
	int line;
	int t_col;
	int t_li;
}				t_posinfo;

char *copybuff;
char *inside_history;

int	read_command(char **line);
int init_termcaps();

#endif
