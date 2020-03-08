/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:27:52 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/17 20:04:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	**ft_tabcpy(char **table)
{
	char	**tab_cpy;
	int		nb;

	nb = 0;
	while (table[nb])
		++nb;
	if (!(tab_cpy = (char**)ft_memalloc(sizeof(char**) * (nb + 1))))
		return (NULL);
	--nb;
	while (nb >= 0)
	{
		if (!(tab_cpy[nb] = ft_strdup(table[nb])))
		{
			++nb;
			while (table[nb])
			{
				ft_memdel((void**)&tab_cpy[nb]);
				++nb;
			}
			free(tab_cpy);
			return (NULL);
		}
		--nb;
	}
	return (tab_cpy);
}
