/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:08:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/17 15:21:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	**ft_tabmalloc(size_t size)
{
	void	**p_mem;

	if (!(p_mem = (void**)malloc(size * sizeof(void*))))
		return (NULL);
	ft_bzero((void*)p_mem, size * sizeof(void*));
	return (p_mem);
}
