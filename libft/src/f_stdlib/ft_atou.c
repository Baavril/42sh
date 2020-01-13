/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:01:44 by yberramd          #+#    #+#             */
/*   Updated: 2020/01/05 13:54:46 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_atou(const char *str)
{
	unsigned long	nbr;
	unsigned int	i;
	unsigned short	val;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		++i;
	while (str[i] > 47 && str[i] < 58)
	{
		val = str[i] ^ ((1 << 5) | (1 << 4));
		nbr = nbr * 10 + val;
		++i;
	}
	return (nbr);
}
