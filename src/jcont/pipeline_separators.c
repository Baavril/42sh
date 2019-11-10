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

#include "pipelines.h"


/* A list is a sequence of one or more pipelines separated by one
** of the operators ‘;’,  ‘&’,‘&&’, or ‘||’, and optionally terminated by
** one of ‘;’, ‘&’, or a newline. Of these list operators, ‘&&’ and ‘||’ have
** equal precedence, followed by ‘;’ and ‘&’, whichhave equal precedence. A
** sequence of one or more newlines may appear in a list to delimit commands,
** equivalent to a semicolon.
*/

static __inline_ _Bool	is_pipeline_separator(const char *str)
{
	int i;
	struct	s_pipeline_separators separators[] =
    { {"||"}, {"&&"}, {";"}, {"&"}, {"\0"} };

	i = 0;
    while (*(separators[i].separator))
    {
        if (!ft_strcmp(str, separators[i].separator))
		return (1);
	++i;
    }
    return (0);
}
