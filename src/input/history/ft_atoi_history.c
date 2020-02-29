/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:20:13 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 15:59:35 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi_history2(const char *str)
{
	int				i;
	unsigned long	nbr;
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
