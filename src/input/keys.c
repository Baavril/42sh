/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:02:02 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/08 18:24:02 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "history.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdint.h>

char	*buff_realloc(char *old_buff, size_t i)
{
	static size_t buff_size = 0;
	char *new_buff;

	if (!*old_buff)
		buff_size = 0;
	if (i > INPUT_SIZE * buff_size)
	{
		buff_size = i / INPUT_SIZE + 1;
		if (!(new_buff = malloc(1 + (buff_size) * INPUT_SIZE)))
			exit(-1);
		ft_strcpy(new_buff, old_buff);
		free(old_buff);
		return (new_buff);
	}
	return (old_buff);
}

void normal_char(char **buff, size_t *j, size_t *i, char c)
{
	*buff = buff_realloc(*buff, ++(*i));
	ft_memmove(&((*buff)[*j + 1]), &((*buff)[*j]), *i - *j);
	(*buff)[(*j)++] = c;
}

void set_string(char **buff, size_t *j, size_t *i, char *str)
{
	size_t len;

	if (!str)
		return;
	len = ft_strlen(str);
	if (*i < len)
		*buff = buff_realloc(*buff, len);
	ft_strcpy(*buff, str);
	*i = len;
	*j = len;
}

void right_arrow(char **buff, size_t *j, size_t *i)
{
	(void) buff;
	if (*j < *i)
		++(*j);
}

void left_arrow(char **buff, size_t *j, size_t *i)
{
	(void) buff;
	(void) i;
	if (*j > 0)
		--(*j);
}

void delete_key(char **buff, size_t *j, size_t *i)
{
	if (*j < *i && *i > 0)
	{
		ft_memmove(&((*buff)[*j]), &((*buff)[*j + 1]), *i - *j);
		--(*i);
	}
}

void backspace_key(char **buff, size_t *j, size_t *i)
{
	if (*i > 0 && *j > 0)
	{
		--(*j);
		ft_memmove(&((*buff)[*j]), &((*buff)[*j + 1]), *i - *j);
		--(*i);
	}
}

/*
 * plus de leaks sur les tab keys -> fonctions a realiser pour prendre en charge autocompletion
 */

void tab_key(char **buff, size_t *j, size_t *i)
{
	char *str;
	char *tmp; 
		
	str = ft_strdup("tabulation");
	tmp = str;
	while (*tmp)
		normal_char(buff, j, i, *tmp++);
	ft_strdel(&str);
}

void down_arrow(char **buff, size_t *j, size_t *i)
{
	char *str;
	if (!inside_history)
		return;
	else if (history(FORWARD, NULL, &str) == 2)
	{
		set_string(buff, i, j, inside_history);
		ft_strdel(&inside_history);
	}
	else
		set_string(buff, i, j, str);
}

void up_arrow(char **buff, size_t *j, size_t *i)
{
	char *str;
	if (!inside_history && (inside_history = ft_strdup(*buff)))
		history(LAST, NULL, &str);
	else
		history(BACKWARD, NULL, &str);
	set_string(buff, i, j, str);
}

void paste_key(char **buff, size_t *j, size_t *i)
{
	char *str = copybuff;
	if (str)
		while (*str)
			normal_char(buff, j, i, *str++);
}

void home_key(char **buff, size_t *j, size_t *i)
{
	(void) buff;
	(void) i;
	*j = 0;
}

void end_key(char **buff, size_t *j, size_t *i)
{
	(void) buff;
	*j = *i;
}

void next_word(char **buff, size_t *j, size_t *i)
{
	(void) i;
	while(*j < *i && ft_isalnum((*buff)[*j]))
			(*j)++;
	while(*j < *i && !ft_isalnum((*buff)[*j]))
			(*j)++;
}

void previous_word(char **buff, size_t *j, size_t *i)
{
	(void) i;
	while(*j > 0 && ft_isalnum((*buff)[*j]))
			(*j)--;
	while(*j > 0 && !ft_isalnum((*buff)[*j]))
			(*j)--;
}

void select_key(char **buff, size_t *j, size_t *i, size_t *u)
{
	(void) i;
	if (*u == SIZE_MAX)
		*u = *j;
	else if (*u != *j)
	{
		ft_strdel(&copybuff);
		if (*j > *u)
			copybuff = ft_strndup(*buff + *u, *j - *u);
		else if (*j < *u)
			copybuff = ft_strndup(*buff + *j, *u - *j);
		*u = SIZE_MAX;
	}
}

void escape_char(char **buff, size_t *j, size_t *i, size_t *u)
{
	char input_buffer[16];

	ft_bzero(input_buffer, 8);
	read(0, input_buffer, 8);

	if (!ft_strcmp(&input_buffer[1], tgetstr("kl", NULL) + 2)) // Cursor Left key
		left_arrow(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kr", NULL) + 2)) // Cursor Right key
		right_arrow(buff, j, i);
	if (!ft_strcmp(&input_buffer[1], tgetstr("ku", NULL) + 2)) // Cursor Up key
		up_arrow(buff, j, i);
	if (!ft_strcmp(&input_buffer[1], tgetstr("kd", NULL) + 2)) // Cursor Down key
		down_arrow(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kD", NULL) + 2)) // Key for delete char under cursor
		delete_key(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kh", NULL) + 2)) // Cursor home key
		home_key(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kN", NULL) + 2)) // key for next page
		next_word(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kP", NULL) + 2)) // key for previous page
		previous_word(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], "F\0")) //FAUX MAIS TEMP
		end_key(buff, j, i);
	else if (!ft_strcmp(&input_buffer[1], "1;2A")) //FAUX MAIS TEMP
		select_key(buff, j, i, u);
	else if (!ft_strcmp(&input_buffer[1], "1;2B")) //FAUX MAIS TEMP
		paste_key(buff, j, i);
}
