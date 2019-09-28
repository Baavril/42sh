/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:11:18 by abarthel          #+#    #+#             */
/*   Updated: 2019/02/18 16:56:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static int	ft_valid(char *base, size_t div)
{
	int i;
	int j;

	i = 0;
	j = 1;
	if (base[0] == '\0' || div == 1 || div == 0)
		return (0);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		while (base[i + j])
		{
			j++;
			if (base[i] == base[i + j])
				return (0);
		}
		i++;
		j = 1;
	}
	return (1);
}

static void	ft_putint(unsigned int nbr, size_t div, char *base)
{
	if (nbr >= div)
	{
		ft_putint(nbr / div, div, base);
		ft_putint(nbr % div, div, base);
	}
	else
		ft_putchar(base[nbr]);
}

void		ft_putnbr_base(int nbr, char *base)
{
	size_t	div;

	div = ft_strlen(base);
	if (ft_valid(base, div) == 0)
		return ;
	if (nbr >= 0)
		ft_putint(nbr, div, base);
	else if (nbr < 0)
	{
		ft_putchar('-');
		ft_putint((nbr * -1), div, base);
	}
}
