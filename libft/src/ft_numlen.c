/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:49:13 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:26:38 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static __inline__ char	ft_numlen_part2(unsigned int nb)
{
	if (nb >= 1000)
	{
		if (nb >= 10000)
			return (5);
		return (4);
	}
	else
	{
		if (nb >= 100)
			return (3);
		if (nb >= 10)
			return (2);
		return (1);
	}
}

extern char			ft_numlen(unsigned int nb)
{
	if (nb >= 100000)
	{
		if (nb >= 10000000)
		{
			if (nb >= 1000000000)
				return (10);
			if (nb >= 100000000)
				return (9);
			return (8);
		}
		if (nb >= 1000000)
			return (7);
		return (6);
	}
	else
		return (ft_numlen_part2(nb));
}
