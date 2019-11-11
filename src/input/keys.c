/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:02:02 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/08 18:24:02 by baavril          ###   ########->fr       */
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

void normal_char(char **buff, t_cursor *cursor, char c)
{
	*buff = buff_realloc(*buff, ++(cursor->start));
	ft_memmove(&((*buff)[cursor->end + 1]), &((*buff)[cursor->end]), cursor->start - cursor->end);
	(*buff)[(cursor->end)++] = c;
}

void set_string(char **buff, t_cursor *cursor, char *str)
{
	size_t len;

	if (!str)
		return;
	len = ft_strlen(str);
	if (cursor->start < len)
		*buff = buff_realloc(*buff, len);
	ft_strcpy(*buff, str);
	cursor->start = len;
	cursor->end = len;
}

void right_arrow(char **buff, t_cursor *cursor)
{
	(void) buff;
	if (cursor->end < cursor->start)
		++(cursor->end);
}

void left_arrow(char **buff, t_cursor *cursor)
{
	(void) buff;
	if (cursor->end > 0)
		--(cursor->end);
}

void delete_key(char **buff, t_cursor *cursor)
{
	if (cursor->end < cursor->start && cursor->start > 0)
	{
		ft_memmove(&((*buff)[cursor->end]), &((*buff)[cursor->end + 1]), cursor->start - cursor->end);
		--(cursor->start);
	}
}

void backspace_key(char **buff, t_cursor *cursor)
{
	if (cursor->start > 0 && cursor->end > 0)
	{
		--(cursor->end);
		ft_memmove(&((*buff)[cursor->end]), &((*buff)[cursor->end + 1]), cursor->start - cursor->end);
		--(cursor->start);
	}
}

/*
 * plus de leaks sur les tab keys -> fonctions a realiser pour prendre en charge autocompletion
 */

void tab_key(char **buff, t_cursor *cursor)
{
	char *str;
	char *tmp; 
		
	str = ft_strdup("tabulation");
	tmp = str;
	while (*tmp)
		normal_char(buff, cursor, *tmp++);
	ft_strdel(&str);
}

void down_arrow(char **buff, t_cursor *cursor)
{
	char *str;
	if (!inside_history)
		return;
	else if (history(FORWARD, NULL, &str) == 2)
	{
		set_string(buff, cursor, inside_history);
		ft_strdel(&inside_history);
	}
	else
		set_string(buff, cursor, str);
}

void up_arrow(char **buff, t_cursor *cursor)
{
	char *str;
	if (!inside_history && (inside_history = ft_strdup(*buff)))
		history(LAST, NULL, &str);
	else
		history(BACKWARD, NULL, &str);
	set_string(buff, cursor, str);
}

void paste_key(char **buff, t_cursor *cursor)
{
	char *str = copybuff;
	if (str)
		while (*str)
			normal_char(buff, cursor, *str++);
}

void home_key(char **buff, t_cursor *cursor)
{
	(void)buff;
	(void)cursor;
	cursor->end = 0;
}

void end_key(char **buff, t_cursor *cursor)
{
	(void) buff;
	cursor->end = cursor->start;
}

void next_word(char **buff, t_cursor *cursor)
{
	while(cursor->end < cursor->start && ft_isalnum((*buff)[cursor->end]))
			(cursor->end)++;
	while(cursor->end < cursor->start && !ft_isalnum((*buff)[cursor->end]))
			(cursor->end)++;
}

void previous_word(char **buff, t_cursor *cursor)
{
	while(cursor->end > 0 && ft_isalnum((*buff)[cursor->end]))
			(cursor->end)--;
	while(cursor->end > 0 && !ft_isalnum((*buff)[cursor->end]))
			(cursor->end)--;
}

void select_key(char **buff, t_cursor *cursor)
{
	if (cursor->in == SIZE_MAX)
		cursor->in = cursor->end;
	else if (cursor->in != cursor->end)
	{
		ft_strdel(&copybuff);
		if (cursor->end > cursor->in)
			copybuff = ft_strndup(*buff + cursor->in, cursor->end - cursor->in);
		else if (cursor->end < cursor->in)
			copybuff = ft_strndup(*buff + cursor->end, cursor->in - cursor->end);
		cursor->in = SIZE_MAX;
	}
}

void escape_char(char **buff, t_cursor *cursor)
{
	char input_buffer[16];

	ft_bzero(input_buffer, 8);
	read(0, input_buffer, 8);

	if (!ft_strcmp(&input_buffer[1], tgetstr("kl", NULL) + 2)) // Cursor Left key
		left_arrow(buff, cursor);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kr", NULL) + 2)) // Cursor Right key
		right_arrow(buff, cursor);
	if (!ft_strcmp(&input_buffer[1], tgetstr("ku", NULL) + 2)) // Cursor Up key
		up_arrow(buff, cursor);
	if (!ft_strcmp(&input_buffer[1], tgetstr("kd", NULL) + 2)) // Cursor Down key
		down_arrow(buff, cursor);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kD", NULL) + 2)) // Key for delete char under cursor
		delete_key(buff, cursor);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kh", NULL) + 2)) // Cursor home key
		home_key(buff, cursor);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kN", NULL) + 2)) // key for next page
		next_word(buff, cursor);
	else if (!ft_strcmp(&input_buffer[1], tgetstr("kP", NULL) + 2)) // key for previous page
		previous_word(buff, cursor);
	else if (!ft_strcmp(&input_buffer[1], "F\0")) //FAUX MAIS TEMP
		end_key(buff, cursor);
	else if (!ft_strcmp(&input_buffer[1], "1;2A")) //FAUX MAIS TEMP
		select_key(buff, cursor);
	else if (!ft_strcmp(&input_buffer[1], "1;2B")) //FAUX MAIS TEMP
		paste_key(buff, cursor);
}
