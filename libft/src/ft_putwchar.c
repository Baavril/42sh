/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:03:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 17:33:48 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "utf8.h"

int	ft_putwchar(wchar_t wc)
{
	char	buf[4];

	if (wc >= 0x00)
	{
		if (wc <= 0x007F)
			return ((write(STDOUT_FILENO, &wc, sizeof(wc))) == -1
					? -1 : (int)wc);
		else
		{
			if (utf8_encoder(&wc) == -1)
				return (-1);
			buf[0] = wc >> 24;
			buf[1] = wc >> 16;
			buf[2] = wc >> 8;
			buf[3] = wc;
			return ((write(STDOUT_FILENO, buf, 4)) == -1
					? -1 : (int)wc);
		}
	}
	else
		return (-1);
}
