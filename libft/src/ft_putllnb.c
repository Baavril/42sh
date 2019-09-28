/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putllnb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 07:11:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/02/19 12:54:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putllnb(long long int n)
{
	unsigned long long int	nb;

	if (n < 0)
		ft_putchar('-');
	nb = n < 0 ? n * -1 : n;
	if (nb >= 10)
	{
		ft_putllnb(nb / 10);
		ft_putchar(nb % 10 + '0');
	}
	else
		ft_putchar(nb + '0');
}
