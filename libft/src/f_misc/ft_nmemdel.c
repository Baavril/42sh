/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmemdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:21:55 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:31:43 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>

#include "libft.h"

void	ft_nmemdel(size_t n, void **ptr, ...)
{
	va_list	ap;

	va_start(ap, ptr);
	ft_memdel(ptr);
	--n;
	while (n)
	{
		ft_memdel(va_arg(ap, void**));
		--n;
	}
	va_end(ap);
}
