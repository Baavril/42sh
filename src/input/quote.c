/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 11:16:45 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/01 11:15:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	next_valid_entry(char current_char, char previous_valid_entry)
{
	if (previous_valid_entry == '\\')
		return (-1);
	else if (previous_valid_entry == '`'
	|| previous_valid_entry == '\"'
	|| previous_valid_entry == '\'')
	{
		if (current_char == previous_valid_entry)
			return (-1);
	}
	else if ((previous_valid_entry == '{' && current_char == '}')
	|| (previous_valid_entry == '(' && current_char == ')'))
		return (-1);
	else if (ft_strchr("{(\'\"`\\\\", current_char))
		return (current_char);
	return (0);
}

char		*quote_prompt(char *command)
{
	char	c;
	char	*buff;
	int		size;

	size = ft_strlen(command);
	if (!(buff = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(buff, size + 1);
	while (*command)
	{
		c = next_valid_entry(*(command++), buff[0] ? buff[ft_strlen(buff) - 1]
													: buff[0]);
		if (c == -1)
			buff[ft_strlen(buff) - 1] = '\0';
		else if (c)
			buff[ft_strlen(buff)] = c;
	}
	if (buff[0])
		if (buff[ft_strlen(buff) - 1] == '\\')
			*(command - 1) = '\0';
	if (buff[0])
		return (buff);
	free(buff);
	return (NULL);
}
