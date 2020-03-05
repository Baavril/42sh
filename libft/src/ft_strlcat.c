/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:42:17 by abarthel          #+#    #+#             */
/*   Updated: 2019/01/29 12:49:55 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ldest;
	size_t	lsrc;
	size_t	i;

	ldest = ft_strlen(dst);
	lsrc = ft_strlen(src);
	i = ft_strlen(dst);
	while (i < size - 1 && *src && size != 0)
	{
		dst[i] = *src;
		++i;
		++src;
	}
	dst[i] = '\0';
	return ((size < ldest) ? size + lsrc : ldest + lsrc);
}
