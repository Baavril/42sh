/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintbits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:25:35 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 21:03:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_fprintbits(char c, int fd)
{
	int		bit;
	char	str[8];

	bit = 0;
	while (bit < 8)
	{
		str[7 - bit] = c & (1 << bit) ? 1 ^ 0x30 : 0;
		++bit;
	}
	return ((int)write(fd, str, 8));
}
