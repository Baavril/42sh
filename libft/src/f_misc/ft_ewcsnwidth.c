/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ewcsnwidth.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:28:19 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/19 17:05:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_wchar.h"

int	ft_ewcsnwidth(const wchar_t *__restrict__ pwcs, size_t n)
{
	size_t	ret;
	int		max_nb_unicode;

	ret = 0;
	max_nb_unicode = 0;
	while (*pwcs)
	{
		ret += ft_ewcwidth(*pwcs);
		if (ret <= n)
			max_nb_unicode = ret;
		else
			break ;
		++pwcs;
	}
	return (max_nb_unicode);
}
