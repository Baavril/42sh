/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 18:48:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "error.h"

int	is_a_valid_chr(const char c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		 || (c >= '0' && c <= '9') || c == '_'))
		return (1);
	else
		return (0);
}

int	is_valid_param(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_a_valid_chr(str[i]))
			return (e_bad_substitution);
		++i;
	}
	return (e_success);
}

size_t	ft_varlen(const char *s, const char *closetag)
{
	size_t	len;
	char	*end;

	len = 0;
	if (*s && !*closetag)
	{
		while (s[len] && is_a_valid_chr(s[len]))
			++len;
		if (s[len] == '?' && len == 0)
			++len;
	}
	else if (*s && *closetag)
	{
		end = ft_strstr(s, closetag);
		if (!end)
			return (len);
		len = (size_t)(end - s);
	}
	return (len);
}
