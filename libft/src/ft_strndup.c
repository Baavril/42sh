/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:20:20 by abarthel          #+#    #+#             */
/*   Updated: 2019/01/29 14:12:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t len)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (!(s2 = (char*)ft_memalloc(sizeof(*s2) * len + 1)))
		return (NULL);
	while (i < len)
	{
		s2[i] = s1[i];
		++i;
	}
	return (s2);
}
