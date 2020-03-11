/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:41:29 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/07 12:36:04 by tgouedar         ###   ########.fr       */
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
