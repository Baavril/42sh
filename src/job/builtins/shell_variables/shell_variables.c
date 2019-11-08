/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 15:07:54 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "shell_variables.h"

#define ISLEGIT 1
#define NOTLEGIT 0

struct s_btree	*g_shellvariables;

static _Bool is_format_legit(const char *input)
{
	const char	*s;

	s = input;
	while (*s)
	{
		if (ft_isalnum(*s) || *s == '_')
			++s;
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