/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_separators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:46:07 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/09 15:46:27 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipelines.h"

/* A list is a sequence of one or more pipelines separated by one
** of the operators ‘;’,  ‘&’,‘&&’, or ‘||’, and optionally terminated by
** one of ‘;’, ‘&’, or a newline. Of these list operators, ‘&&’ and ‘||’ have
** equal precedence, followed by ‘;’ and ‘&’, whichhave equal precedence. A
** sequence of one or more newlines may appear in a list to delimit commands,
** equivalent to a semicolon.
*/

static const struct s_pipeline_separators g_separators[] =
{ {"||"}, {"&&"}, {";"}, {"&"}, {"\0"} };

extern __inline__ _Bool	is_pipeline_separator(const char *str)
{
	int i;

	i = 0;
    while (*(g_separators[i].sep))
    {
        if (!ft_strcmp(str, g_separators[i].sep))
		    return (1);
	    ++i;
    }
    return (0);
}
