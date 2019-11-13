/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parser_shell_variables.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:52:45 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/09 10:07:00 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "parser_utils_shvar.h"

int				recursive_assignement(struct s_assign *var, char *str)
{
	(void)var;
	(void)str;
	return (e_success);
}

static __inline__ int	has_legit_index(const char *input, const char *s)
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
	return (HASINDEX);
}

int				is_format_legit(const char *input)
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

void 			display_assignement_error(char *str)
{
    char *end_ptr;
    char *start_ptr;

    start_ptr = ft_strdup(str);
    end_ptr = start_ptr;
    while (*end_ptr && *end_ptr != '=')
        ++end_ptr;
    *end_ptr = '\0';
    ft_dprintf(STDERR_FILENO, "%s: %s: cannot assign list to array member\n", g_progname, start_ptr);
    ft_memdel((void**)&start_ptr);
}