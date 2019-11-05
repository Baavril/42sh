/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:14:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/06 12:00:49 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strendcpy(char *dst, const char *src)
{
	size_t	count;

	count = 0;
	while (src[count])
	{
		dst[count] = src[count];
		++count;
	}
	dst[count] = '\0';
	return (&dst[count]);
}
