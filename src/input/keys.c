/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys->c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42->fr>                    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:02:02 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/12 14:17:42 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "history.h"
#include "keys.h"
#include "display.h"
#include "auto_completion.h"
#include "prompt.h"

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

int normal_char(char **buff, t_cursor *cursor, char c)
{
	*buff = buff_realloc(*buff, ++(cursor->end));
	ft_memmove(&((*buff)[cursor->start + 1]), &((*buff)[cursor->start]), cursor->end - cursor->start);
	(*buff)[(cursor->start)++] = c;
	return (1);
}

char *get_history(char **buff, t_cursor *cursor)
{
	char *tmp;
	int idx_tmp;
	static int idx_buff = 0;
	static char *match = NULL;

	tmp = NULL;
	if ((idx_tmp = history(SEARCH, buff, &tmp)) >= 1)
	{
		if (match)
			ft_strdel(&match);
		if (!(match = ft_strdup(tmp)))
			return (NULL);
		idx_buff = idx_tmp;
		cursor->match_ret = 0;
		cursor->start = idx_buff;
		return (match);
	}
	cursor->match_ret = 1;
	cursor->start = idx_buff;
	return (match);
}

int set_string(char **buff, t_cursor *cursor, char *str)//set line
{
	size_t len;

	if (!str)
		return (1);
	len = ft_strlen(str);
	if (cursor->end < len)
		*buff = buff_realloc(*buff, len);
	ft_strcpy(*buff, str);
	cursor->end = len;
	cursor->start = len;
	return (1);
}

int right_arrow(char **buff, t_cursor *cursor)
{
	(void)buff;
	if (cursor->start < cursor->end)
		++(cursor->start);
	return (1);
}

int left_arrow(char **buff, t_cursor *cursor)
{
	(void)buff;
	if (cursor->start > 0)
		--(cursor->start);
	return (1);
}

int delete_key(char **buff, t_cursor *cursor)
{
	if (cursor->start < cursor->end && cursor->end > 0)
	{
		ft_memmove(&((*buff)[cursor->start]), &((*buff)[cursor->start + 1]), cursor->end - cursor->start);
		--(cursor->end);
	}
	return (1);
}

int backspace_key(char **buff, t_cursor *cursor)
{
	if (cursor->end > 0 && cursor->start > 0)
	{
		--(cursor->start);
		ft_memmove(&((*buff)[cursor->start]), &((*buff)[cursor->start + 1]), cursor->end - cursor->start);
		--(cursor->end);
	}
	return (1);
}

/*
 * plus de leaks sur les tab keys -> fonctions a realiser pour prendre en charge autocompletion
 */

/***********************************************AUTOCOMPLETION*********************************************************/

static int pos_start(char *input, int start)
{
	if (ft_isspace(input[start]) || input[start] == '/' || input[start] == '|' || input[start] == '&' || input[start] == ';')
		start--;
	if (!ft_isspace(input[start]))
	{
		while (start > 0 && !ft_isspace(input[start]) && input[start] != '/' && !(input[start] == '|' || input[start] == '&' || input[start] == ';'))
			start--;
		if (ft_isspace(input[start]) || input[start] == '/' || input[start] == '|' || input[start] == '&' || input[start] == ';')
			start++;
	}
	return (start);
}

static char *ft_add_string(char *input, char **binary, int start)
{
	char 	*tmp;
	int 	len;
	int 	i;
	int 	y;

	i = 0;
	start = pos_start(input, start);
	y = start;
	while (input[y] != '\0' && input[y] == (*binary)[i])
	{
		y++;
		i++;
	}
	len = ft_strlen((*binary)) - i;
	if (!(tmp = (char*)malloc(sizeof(char) * (len + ft_strlen(input) + 1))))
		return (NULL);
	len = i;
	i = 0;
	while (i < start)
	{
		tmp[i] = input[i];
		i++;
	}
	y = 0;
	while ((*binary)[y] != '\0')
	{
		tmp[i] = (*binary)[y];
		i++;
		y++;
	}
	start = start + len;
	while (input[start] != '\0')
	{
		tmp[i] = input[start];
		start++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static int 	cmp_binary(char *str1, char *str2, int y, char *input)
{
	int i;
	int tmp_y;

	tmp_y = y;
	i = 0;
	y = 0;
	while (str1[i] != '\0' && input[i] != '\0' && str1[i] == input[i])
		i++;
	while (str1[i] !='\0' && str2[i] != '\0' && str1[i] == str2[i])
	{
		i++;
		y++;
	}
	if (tmp_y != -1)
		return ((tmp_y < y) ? tmp_y : y);
	else
		return (y);
}

static void assign_tmp(char *tmp, char *binary, char *input, int y)
{
	int i;

	i = 0;
	while (input[i] == binary[i])
	{
		tmp[i] = binary[i];
		i++;
	}
	while (i < y)
	{
		tmp[i] = binary[i];
		i++;
	}
	tmp[i] = '\0';
}

static int ft_strlen_modif(char *str)
{
	int i;

	i = 0;
	while (str && str[i] != '\0' && !ft_isspace(str[i]) && str[i] != '/' && str[i] != '|' && str[i] != '&' && str[i] != ';')
		i++;
	return (i);
}

static int 	dynamic_completion(char **binary, char *input, char **equal, int start)
{
	int 	i;
	int 	y;
	int 	tmp_start;
	char 	*tmp;

	tmp_start = pos_start(input, start);
	y = -1;
	i = 1;
	tmp = binary[0];
	while (binary[i] != NULL && y != 0 && binary[0])
	{
		y = cmp_binary(binary[i], tmp, y, &input[tmp_start]);
		tmp = binary[i];
		i++;
	}
	if (y == 0 || y == -1)
		return (2);
	y += ft_strlen_modif(&input[tmp_start]);
	if (!(tmp = (char*)malloc(sizeof(char) * (y + 1))))
		return (0);
	assign_tmp(tmp, binary[0], &input[tmp_start], y);
	if (!((*equal) = ft_add_string(input, &tmp, start)))	
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int tab_key(char **buff, t_cursor *cursor)
{
	int 	ret;
	t_tst 	*tst;
	char 	**binary;
	char 	*input;

	input = NULL;
	if (!cursor->end)
		return (1);
	tst = ft_tst();
	if (!(ret = ft_auto_completion(tst, *buff, &binary, cursor->start)))// curseur !!!!!!
	{
		del_tst(tst);
		return (0);
	}
	if (ret == 2)
	{
		if (!(input = ft_add_string(*buff, &binary[0], cursor->start)))
		{
			del_tst(tst);
			del_double_char(binary);
			return (0);
		}
		ft_printf("path = [%s]\n", binary[0]);
		set_string(buff, cursor, input);
		ft_strdel(&input);
	}
	else if (binary && binary[0] != NULL)
	{
		if ((ret = dynamic_completion(binary, *buff, &input, cursor->start)) == 1)
		{
			set_string(buff, cursor, input);
			ft_strdel(&input);
		}
		else if (ret == 0)
		{
			del_tst(tst);
			del_double_char(binary);
			return (0);
		}
		print_double_char(binary);//FAIRE UN display
	}
	//printf("ret = %d\n", ret);
	del_tst(tst);
	if (binary)
		del_double_char(binary);
	return (1);
}

/**********************************************************************************************************************/

int down_arrow(char **buff, t_cursor *cursor)
{
	char *str;

	str = NULL;
	if (!inside_history)
		return (1);
	else if (history(FORWARD, NULL, &str) == 2)
	{
		set_string(buff, cursor, inside_history);
		ft_strdel(&inside_history);
	}
	else
		set_string(buff, cursor, str);
	return (1);
}

int up_arrow(char **buff, t_cursor *cursor)
{
	char *str;

	str = NULL;
	if (!inside_history && (inside_history = ft_strdup(*buff)))
		history(LAST, NULL, &str);
	else
		history(BACKWARD, NULL, &str);
	set_string(buff, cursor, str);
	return (1);
}

int paste_key(char **buff, t_cursor *cursor)
{
	char *str = copybuff;
	if (str)
		while (*str)
			normal_char(buff, cursor, *str++);
	return (1);
}

int home_key(char **buff, t_cursor *cursor)
{
	(void)buff;
	cursor->start = 0;
	return (1);
}

int end_key(char **buff, t_cursor *cursor)
{
	(void)buff;
	cursor->start = cursor->end;
	return (1);
}

int next_word(char **buff, t_cursor *cursor)
{
	while(cursor->start < cursor->end && ft_isalnum((*buff)[cursor->start]))
		(cursor->start)++;
	while(cursor->start < cursor->end && !ft_isalnum((*buff)[cursor->start]))
		(cursor->start)++;
	return (1);
}

int previous_word(char **buff, t_cursor *cursor)
{
	while(cursor->start > 0 && ft_isalnum((*buff)[cursor->start]))
		(cursor->start)--;
	while(cursor->start > 0 && !ft_isalnum((*buff)[cursor->start]))
		(cursor->start)--;
	return (1);
}

int select_key(char **buff, t_cursor *cursor)
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
	return (1);
}
