/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:25:22 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/20 11:41:51 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdio.h>
#include <stdint.h>


static int display_select(char *str, size_t start, size_t end)
{
	size_t swap;
	if (start > end)
	{
		swap = start;
		start = end;
		end = swap;
	}
	write(1, str, start);
	ft_putstr(tgetstr("mr", NULL));
	write(1, &str[start], end - start);
	ft_putstr(tgetstr("me", NULL));
	ft_putstr(&str[end]);
	return(0);
}

static int display_all(char *str, size_t j, size_t i, size_t u, char *prompt, size_t prompt_len)
{
	size_t col = tgetnum("co");
	char c;

	c = '\0';
	ft_putstr(tgetstr("cr", NULL));
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(prompt);
	if (u == SIZE_MAX || u > i)
		ft_putstr(str);
	else
		display_select(str, j, u);
	if (!((i + prompt_len) % col))
		write(1, "\n", 1);
	return((j + prompt_len) / col);
}

int display(char *str, size_t j, size_t i, size_t u, char *prompt, size_t prompt_len)
{
	size_t col = tgetnum("co");
	size_t x;
	static size_t lines_offset = 0;

	x = 0;

	// sets lines_offset value to normal if string is empty : ISSUE HERE
	if (i == j && i == 0) // We enter this when opening a new, fresh prompt (usually after entering a command). This test is just not enough !
		lines_offset = prompt_len / col;

	//use the value of lines_offset
	while (lines_offset--)
		ft_putstr(tgetstr("up", NULL));

	//reset lines_offset value and display text
	lines_offset = display_all(str, j, i, u, prompt, prompt_len);

	//Reposition cursor
	x = ((i + prompt_len) / col) - lines_offset;
	while (x--)
		ft_putstr(tgetstr("up", NULL));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (j + prompt_len) % col));

	return(0);
}
