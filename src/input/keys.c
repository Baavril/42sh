/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:02:02 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/13 15:34:03 by baavril          ###   ########.fr       */
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
	*buff = buff_realloc(*buff, ++(cursor->end));
	ft_memmove(&((*buff)[cursor->start + 1]), &((*buff)[cursor->start]), cursor->end - cursor->start);
	(*buff)[(cursor->start)++] = c;
}

void set_string(char **buff, t_cursor *cursor, char *str)
{
	size_t len;

	if (!str)
		return;
	len = ft_strlen(str);
	if (cursor->end < len)
		*buff = buff_realloc(*buff, len);
	ft_strcpy(*buff, str);
	cursor->end = len;
	cursor->start = len;
}

void right_arrow(char **buff, t_cursor *cursor)
{
	(void) buff;
	if (cursor->start < cursor->end)
		++(cursor->start);
}

void left_arrow(char **buff, t_cursor *cursor)
{
	(void) buff;
	if (cursor->start > 0)
		--(cursor->start);
}

void delete_key(char **buff, t_cursor *cursor)
{
	if (cursor->start < cursor->end && cursor->end > 0)
	{
		ft_memmove(&((*buff)[cursor->start]), &((*buff)[cursor->start + 1]), cursor->end - cursor->start);
		--(cursor->end);
	}
}

void backspace_key(char **buff, t_cursor *cursor)
{
	if (cursor->end > 0 && cursor->start > 0)
	{
		--(cursor->start);
		ft_memmove(&((*buff)[cursor->start]), &((*buff)[cursor->start + 1]), cursor->end - cursor->start);
		--(cursor->end);
	}
}

void	search_history(char **buff, t_cursor *cursor)
{
	(void)buff;
	(void)cursor;
	while (1)
		ft_putendl("Search History");
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
	cursor->start = 0;
}

void end_key(char **buff, t_cursor *cursor)
{
	(void) buff;
	cursor->start = cursor->end;
}

void next_word(char **buff, t_cursor *cursor)
{
	while(cursor->start < cursor->end && ft_isalnum((*buff)[cursor->start]))
			(cursor->start)++;
	while(cursor->start < cursor->end && !ft_isalnum((*buff)[cursor->start]))
			(cursor->start)++;
}

void previous_word(char **buff, t_cursor *cursor)
{
	while(cursor->start > 0 && ft_isalnum((*buff)[cursor->start]))
			(cursor->start)--;
	while(cursor->start > 0 && !ft_isalnum((*buff)[cursor->start]))
			(cursor->start)--;
}

void select_key(char **buff, t_cursor *cursor)
{
	if (cursor->in == SIZE_MAX)
		cursor->in = cursor->start;
	else if (cursor->in != cursor->start)
	{
		ft_strdel(&copybuff);
		if (cursor->start > cursor->in)
			copybuff = ft_strndup(*buff + cursor->in, cursor->start - cursor->in);
		else if (cursor->start < cursor->in)
			copybuff = ft_strndup(*buff + cursor->start, cursor->in - cursor->start);
		cursor->in = SIZE_MAX;
	}
}
