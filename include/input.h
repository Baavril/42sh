/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:11:17 by bprunevi          #+#    #+#             */
/*   Updated: 2019/09/29 11:48:08 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define INPUT_SIZE 16
# define PROMPT_CHARS " 21sh > "

typedef struct 	s_posinfo
{
	int fd;
	int line;
	int t_col;
	int t_li;
}				t_posinfo;

t_posinfo g_pi;

int	read_command(char **line);
int init_termcaps();

#endif
