/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:46:50 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 15:07:53 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		p_dst[i] = p_src[i];
		if (p_src[i] == (unsigned char)c)
			return (&p_dst[++i]);
		++i;
	}
	return (NULL);
}
