/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputws.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:25:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 13:57:26 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_wchar.h"

int	ft_fputws(const wchar_t *restrict ws, int fd)
{
	int		ret;
	size_t	i;

	i = 0;
	if (ws && *ws)
	{
		while (ws[i])
		{
			if ((ret = ft_fputwc(ws[i], fd)) == -1)
				return (ret);
			else
				++i;
		}
		return (ret);
	}
	return (-1);
}
