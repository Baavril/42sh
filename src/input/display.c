/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:25:22 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/11 15:05:46 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdio.h>

int display_all(char *str, int j, int i, char *prompt, int prompt_len)
{
	int col = tgetnum("co");
	ft_putstr(tgetstr("cr", NULL));
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(prompt);
	ft_putstr(str);
	if (!((i + prompt_len) % col))
		write(1, "\n", 1);
	return((j + prompt_len) / col);
}

/*
int refresh_line(int prompt_len, int line, char *str)
{
	(void) prompt_len;
	int col = tgetnum("co");
	ft_putstr(tgetstr("cr", NULL));
	ft_putstr(tgetstr("ce", NULL));
	if (ft_strlen(str) < (unsigned long)(line * col))
		return(1);
	str += line * col;
	while (*str && col--)
		write(1, str++, 1);
	return(0);
}
*/

int display(char *str, int j, int i, char *prompt, int prompt_len)
{
	int col = tgetnum("co");
	int x;
	static int lines_offset = 0;

	x = 0;

	// set lines_offset value to normal if string is empty (ISSUE HERE : may overwrite previous lines when prompt is 1+ lines long)
	if (i == j && i == 0)
		lines_offset = prompt_len / col;

	//use the value of lines_offset
	while (lines_offset--)
		ft_putstr(tgetstr("up", NULL));

	//reset lines_offset value and display text
	lines_offset = display_all(str, j, i, prompt, prompt_len);

	//Reposition cursor
	x = ((i + prompt_len) / col) - lines_offset;
	while (x--)
		ft_putstr(tgetstr("up", NULL));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (j + prompt_len) % col));

	return(0);
}
