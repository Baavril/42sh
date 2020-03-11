/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_upphexa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:11:18 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 17:32:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_putint(unsigned int nbr, char *base)
{
	if (nbr >= 16)
	{
		ft_putint(nbr / 16, base);
		ft_putint(nbr % 16, base);
	}
	else
		ft_putchar(base[nbr]);
}

void		ft_putnbr_upphexa(int nbr)
{
	char	*base;

	base = "0123456789ABCDEF\0";
	if (nbr >= 0)
		ft_putint(nbr, base);
	else if (nbr < 0)
	{
		ft_putchar('-');
		ft_putint((nbr * -1), base);
	}
}
