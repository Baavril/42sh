/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:05:22 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/09 20:07:16 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isnumber_base(char *to_test, const char *base)
{
	size_t	i;

	i = 0;
	while (to_test[i])
	{
		if (!(ft_isin(to_test[i], base)))
			return (0);
		i++;
	}
	return (1);
}
