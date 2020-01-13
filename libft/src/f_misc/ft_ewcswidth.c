/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ewcswidth.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:28:19 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:34:17 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ewcswidth(const wchar_t *restrict pwcs)
{
	int	len;

	len = 0;
	while (*pwcs)
	{
		if (*pwcs < 0)
			return (0);
		if (*pwcs <= 0x007F)
			len += 1;
		else if (*pwcs <= 0x07FF)
			len += 2;
		else if (*pwcs <= 0xFFFF)
			len += 3;
		else if (*pwcs <= 0x10FFFF)
			len += 4;
		else
			return (0);
		++pwcs;
	}
	return (len);
}
