/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:34:40 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 14:45:57 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "history.h"

char		*buff_realloc(char *old_buff, size_t i)
{
	static size_t	buff_size = 0;
	char			*new_buff;

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

int			normal_char(char **buff, t_cursor *cursor, char c)
{
	*buff = buff_realloc(*buff, ++(cursor->end));
	ft_memmove(&((*buff)[cursor->start + 1]), &((*buff)[cursor->start]),
			cursor->end - cursor->start);
	(*buff)[(cursor->start)++] = c;
	return (1);
}

char		*get_history(char **buff, t_cursor *cursor)
{
	char		*tmp;
	int			idx_tmp;
	static int	idx_buff = 0;
	static char	*match = NULL;

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

int			set_string(char **buff, t_cursor *cursor, char *str)
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
