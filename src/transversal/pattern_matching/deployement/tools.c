/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:29:59 by baavril           #+#    #+#             */
/*   Updated: 2020/02/02 18:31:35 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "globing.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

int	get_btw_square(char **match)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (*match[i] == CL_SQUAR)
	{
		free(*match);
		if (!(*match = ft_strdup(EMPTY_STR)))
			return (0);
		return (SUCCESS);
	}
	if (!(tmp = (char*)ft_memalloc(sizeof(char) * (ft_strlen(*match) + 1))))
		return (0);
	while ((*match)[i] && (*match)[i] != CL_SQUAR)
	{
		tmp[i] = (*match)[i];
		i++;
	}
	tmp[i + 1] = '\0';
	free(*match);
	*match = tmp;
	return (SUCCESS);
}
