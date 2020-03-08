/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:25:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:31:03 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_wchar.h"

int		ft_putwstr(const wchar_t *restrict ws)
{
	int		ret;
	size_t	i;

	i = 0;
	if (ws && *ws)
	{
		while (ws[i])
		{
			if ((ret = ft_fputwc(ws[i], STDOUT_FILENO)) == -1)
				return (ret);
			else
				++i;
		}
		return (ret);
	}
	return (-1);
}
