/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 10:55:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 17:30:59 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_putint(size_t nbr, char *base)
{
	if (nbr >= 16)
	{
		ft_putint(nbr / 16, base);
		ft_putint(nbr % 16, base);
	}
	else
		ft_putchar(base[nbr]);
}

static void	ft_putnbrhexa(size_t nbr)
{
	char	*base;

	base = "0123456789abcdef\0";
	ft_putint(nbr, base);
}

void		ft_putaddr(void **ptr)
{
	ft_putstr("0x");
	ft_putnbrhexa((size_t)ptr);
}
