/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parser_shell_variables.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:52:45 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/08 17:55:05 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_utils_shvar.h"

#define ISLEGIT 1
#define NOTLEGIT 0

static __inline__ _Bool has_legit_index(const char *input, const char *s)
{
	++s;
	input = s;
	while (*s && ft_isalnum(*s))
		++s;
	if (!*s || *s !=']' || input == s)
		return (NOTLEGIT);
	++s;
	if (*s != '=')
		return (NOTLEGIT);
	return (ISLEGIT);
}

_Bool is_format_legit(const char *input)
{
	const char	*s;

	s = input;
	while (*s)
	{
		if (ft_isalnum(*s) || *s == '_')
			++s;
		else if (*s == '[')
			return (has_legit_index(input, s));
		else if (*s == '=')
		{
			if (s != input)
			    return (ISLEGIT);
			else
				return (NOTLEGIT);
		}
		else
			return (NOTLEGIT);
	}
	return (NOTLEGIT);
}
