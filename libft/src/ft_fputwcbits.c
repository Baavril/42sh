/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputwcbits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:25:35 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 21:04:38 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		ft_fputwcbits(wchar_t c, int fd)
{
	int		bit;
	char	str[32];

	if (sizeof(wchar_t) == 4)
	{
		bit = 0;
		while (bit < 32)
		{
			str[31 - bit] = c & (1 << bit) ? 1 ^ 0x30 : 0;
			++bit;
		}
		return ((int)write(fd, str, 32));
	}
	else
		return (-1);
}
