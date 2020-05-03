/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:53:53 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/12 12:05:15 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa64(int64_t nb)
{
	char			*res;
	int64_t			j;
	size_t			i;
	int				s;

	if (nb < 0 && !(nb - 1))
		return (ft_strdup("-9223372036854775808"));
	i = 0;
	s = (nb < 0 ? -1 : 1);
	j = s * nb;
	while (++i && j)
		j /= 10;
	((s < 0 || !nb) ? 1 : --i);
	if (!(res = ft_strnew(i)))
		return (NULL);
	while (i > 0)
	{
		j = (s * nb) % 10;
		res[--i] = (ft_isdigit(j + '0') ? j + '0' : -1 * j + '0');
		nb /= 10;
	}
	(s < 0 ? res[0] = '-' : 1);
	return (res);
}
