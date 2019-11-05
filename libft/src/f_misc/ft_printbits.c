/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:25:35 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 17:30:30 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_printbits(char c)
{
	int		bit;
	char	str[8];

	bit = 0;
	while (bit < 8)
	{
		str[7 - bit] = c & (1 << bit) ? 1 ^ 0x30 : 0;
		++bit;
	}
	return ((int)write(STDOUT_FILENO, str, 8));
}
