/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 11:16:45 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/09 17:44:31 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	next_valid_entry(char current_char, char previous_valid_entry)
{
	//ft_printf("nva(%c,%c)", current_char, previous_valid_entry);
	if (previous_valid_entry == '`' || previous_valid_entry == '\"' || previous_valid_entry == '\'')
	{
		if (current_char == previous_valid_entry)
			return(-1);
	}
	else if (previous_valid_entry == '{' && current_char == '}')
		return(-1);
	else if (previous_valid_entry == '(' && current_char == ')')
		return(-1);
	else if (ft_strchr("{(\'\"`", current_char))
		return (current_char);
	return(0);
}

char *quote_prompt(char *command)
{
	char c;
	char *buff;
	int size;

	size = ft_strlen(command) + 1;
	if (!(buff = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(buff, size);
	if (command[size - 1] == '\\')
	{
		command[size - 1] = '\0';
		buff[0] = '\\';
	}
	while (*command)
	{
		c = next_valid_entry(*(command++) , buff[0] ? buff[ft_strlen(buff) - 1] : buff[0]);
		if (c == -1)
			buff[ft_strlen(buff) - 1] = '\0';
		else if (c)
			buff[ft_strlen(buff)] = c;
	}
	if (buff[0])
		return (buff);
	free(buff);
	return(NULL);
}
