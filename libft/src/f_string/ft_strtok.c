/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 10:44:25 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:25:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static __inline__ _Bool		isdelim(char c, const char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		++delim;
	}
	return (0);
}

char					*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	char		*token;

	token = NULL;
	if (str)
		s = str;
	if (*s == '\0')
		return (NULL);
	while (isdelim(*s, delim))
		++s;
	token = s;
	while (!isdelim(*s, delim))
	{
		if (*s == '\0')
			return (token);
		++s;
	}
	while (isdelim(*s, delim))
	{
		*s = '\0';
		++s;
	}
	return (token);
}
