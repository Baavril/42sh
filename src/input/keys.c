/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:02:02 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/14 17:30:03 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>

char	*buff_realloc(char *buff, int buff_size)
{
	char *rtn;

	if (!(rtn = malloc(1 + buff_size * INPUT_SIZE)))
		exit(-1);
	ft_strcpy(rtn, buff);
	free(buff);
	return (rtn);
}

void normal_char(char **buff, int *j, int *i, char c)
{
	static int buff_size = 0;

	if (!**buff)
		buff_size = 0;
	++(*i);
	if (*i > INPUT_SIZE * buff_size)
		*buff = buff_realloc(*buff, ++buff_size);
	ft_memmove(&((*buff)[*j + 1]), &((*buff)[*j]), *i - *j);
	(*buff)[(*j)++] = c;
}

void right_arrow(char **buff, int *j, int *i)
{
	(void) buff;
	if (*j < *i)
		++(*j);
}

void left_arrow(char **buff, int *j, int *i)
{
	(void) buff;
	(void) i;
	if (*j > 0)
		--(*j);
}

void delete_key(char **buff, int *j, int *i)
{
	if (*j < *i && *i > 0)
	{
		ft_memmove(&((*buff)[*j]), &((*buff)[*j + 1]), *i - *j);
		--(*i);
	}
}

void backspace_key(char **buff, int *j, int *i)
{
	if (*i > 0 && *j > 0)
	{
		--(*j);
		ft_memmove(&((*buff)[*j]), &((*buff)[*j + 1]), *i - *j);
		--(*i);
	}
}

void tab_key(char **buff, int *j, int *i)
{
	char *str = ft_strdup("tabulation");
	while (*str)
		normal_char(buff, j, i, *str++);
}


void home_key(char **buff, int *j, int *i)
{
	(void) buff;
	(void) i;
	*j = 0;
}

void end_key(char **buff, int *j, int *i)
{
	(void) buff;
	*j = *i;
}

void next_word(char **buff, int *j, int *i)
{
	(void) i;
	while(*j < *i && ft_isalnum((*buff)[*j]))
			(*j)++;
	while(*j < *i && !ft_isalnum((*buff)[*j]))
			(*j)++;
}

void previous_word(char **buff, int *j, int *i)
{
	(void) i;
	while(*j > 0 && ft_isalnum((*buff)[*j]))
			(*j)--;
	while(*j > 0 && !ft_isalnum((*buff)[*j]))
			(*j)--;
}

void escape_char(char **buff, int *j, int *i)
{
	char input_buffer[16];

	ft_bzero(input_buffer, 16);
	read(0, input_buffer, 16);

	if (!ft_strcmp(&input_buffer[1], tgetstr("kl", NULL) + 2))
		left_arrow(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kr", NULL) + 2))
		right_arrow(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kD", NULL) + 2))
		delete_key(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kh", NULL) + 2))
		home_key(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kN", NULL) + 2))
		next_word(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kP", NULL) + 2))
		previous_word(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], "F\0")) //FAUX MAIS TEMP
		end_key(buff, j, i);
}
