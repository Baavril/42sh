/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_octal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:11:18 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 17:34:35 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_putint(unsigned int nbr, const char *base)
{
	if (nbr >= 8)
	{
		ft_putint(nbr / 8, base);
		ft_putint(nbr % 8, base);
	}
	else
		ft_putchar(base[nbr]);
}

void		ft_putnbr_octal(int nbr)
{
	if (nbr >= 0)
		ft_putint(nbr, "01234567OCTAL_BASE");
	else if (nbr < 0)
	{
		ft_putchar('-');
		ft_putint((nbr * -1), "01234567OCTAL_BASE");
	}
}
