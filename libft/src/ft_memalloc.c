/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:08:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/17 15:21:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*p_mem;

	if (!(p_mem = (void*)malloc(size)))
		return (NULL);
	ft_bzero(p_mem, size);
	return (p_mem);
}
