/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 12:57:00 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 14:50:47 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;

	i = -1;
	cpy = (char*)malloc(sizeof(*cpy) * len + 1);
	if (!cpy || !s)
		return (NULL);
	++i;
	while (i < len)
	{
		cpy[i] = s[start + i];
		++i;
	}
	cpy[i] = '\0';
	return (cpy);
}
