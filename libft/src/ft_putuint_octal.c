/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_octal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:11:18 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 17:35:00 by abarthel         ###   ########.fr       */
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

void		ft_putuint_octal(unsigned int nbr)
{
	ft_putint(nbr, "01234567OCTAL_BASE");
}
