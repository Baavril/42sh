/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:48:52 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 09:52:00 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

/*
** PRINT_QUOTE
** Displays the corresponding quote message according to the mask value.
** ` -> bquote
** { -> cursh
** ( -> subsh
** " -> dquote
** ' -> quote
*/

static void		print_quote(char mask)
{
	if (mask == '`')
		ft_printf("bquote> ");
	else if (mask == '\"')
		ft_printf("dquote> ");
	else if (mask == ((1 << 1) | (1 << 2)))
		ft_printf("cursh> ");
	else if (mask == (1 << 0))
		ft_printf("subsh> ");
	else if (mask == '\'')
		ft_printf("quote> ");
}

static char		is_quote_open(char c, char mask)
{
	if (c == '`' && (mask == '`' || !mask))
		mask ^= '`';
	else if (c == '\"' && (mask == '\"' || !mask))
		mask ^= '\"';
	else if ((c == '{' && !mask) || (c == '}' && mask == ((1 << 1) | (1 << 2))))
		mask ^= ((1 << 1) | (1 << 2));
	else if ((c == '(' && !mask) || (c == ')' && mask == (1 << 0)))
		mask ^= (1 << 0);
	else if (c == '\'' && (mask == '\'' || !mask))
		mask ^= '\'';
	return (mask);
}

static char		*create_new_line(char *str, int *len)
{
	char	*new_line;

	new_line = (char*)ft_memalloc(*len);
	if (!new_line)
	{
		*len = -1;
		return (NULL);
	}
	else
	{
		if (str)
		{
			new_line = ft_strncpy(new_line, str, *len);
			free(str);
		}
		return (new_line);
	}
}

int				get_block(char **line, int len, char separator)
{
	int		ret;
	static char	mask;
	char		c;

	ret = 0;
	while (ret < len)
	{	
		c = ft_getch();
		if (c == -1)
			return (-2);
		mask = is_quote_open(c, mask);
		if ((c == separator && !mask) || !c)
		{
			(*line)[ret] = 0;
			return (ret);
		}
		else if (c == separator && mask)
			print_quote(mask);
		(*line)[ret] = c;
		++ret;
	}
	if (ret == len)
		return (-1);
	else
		return (1);
}

int				get_stdin(char **line)
{
	int		len;
	int		ret;
	char	*new_line;

	len = 0;
	ret = 0;
	new_line = NULL;
	while (1)
	{
		len += 128;
		new_line = create_new_line(new_line, &len);
		if (len == -1)
			return (-1);
		*line = new_line;
		if ((ret = get_block(line, len, '\n')) == -1)
			continue ;
		if (ret == -2)
		{
			ft_memdel((void**)line);
			return (-1);
		}
		else
			return (1);
	}
	return (ret);
}
