/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_rangecpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 20:44:46 by tgouedar          #+#    #+#             */
/*   Updated: 2019/11/13 12:16:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char			**ft_tab_rangecpy(char **table, size_t start, size_t end)
{
	char		**tab_cpy;
	int			nb;
	size_t		i;

	if (!table)
		return (NULL);
	nb = ft_tablen(table);
	if ((end > (size_t)nb || (nb = end - start + 1) <= 0) \
	|| !(tab_cpy = (char**)ft_memalloc(sizeof(char**) * (nb + 1))))
		return (NULL);
	i = nb;
	tab_cpy[i--] = NULL;
	nb = end;
	while ((size_t)nb >= start)
	{
		if (!(tab_cpy[i--] = ft_strdup(table[nb])))
		{
			while ((size_t)nb <= end)
			{
				ft_memdel((void**)&tab_cpy[++i]);
				++nb;
			}
			free(tab_cpy);
			return (NULL);
		}
		nb--;
	}
	return (tab_cpy);
}
