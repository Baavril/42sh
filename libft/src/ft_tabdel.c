/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:41:29 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/06 21:49:08 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_tabdel(char ***tables)
{
	size_t	i;

	i = 0;
	if (tables && *tables)
	{
		while ((*tables)[i])
		{
			free((*tables)[i]);
			(*tables)[i] = NULL;
			++i;
		}
		free((*tables)[i]);
		free(*tables);
		tables = NULL;
	}
}
