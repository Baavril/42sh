/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputwc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:07:08 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 16:53:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "utf8.h"

int	ft_fputwc(wchar_t wc, int fd)
{
	char	buf[4];

	if (wc >= 0x00)
	{
		if (wc <= 0x007F)
			return ((write(fd, &wc, sizeof(wc))) == -1
					? -1 : (int)wc);
		else
		{
			if (utf8_encoder(&wc) == -1)
				return (-1);
			buf[0] = wc >> 24;
			buf[1] = wc >> 16;
			buf[2] = wc >> 8;
			buf[3] = wc;
			return ((write(fd, buf, 4)) == -1
					? -1 : (int)wc);
		}
	}
	else
		return (-1);
}
