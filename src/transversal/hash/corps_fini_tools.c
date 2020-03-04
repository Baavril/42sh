/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corps_fini_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:56:53 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/13 21:59:51 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

uint64_t		ft_sq_mod(uint64_t to_sq, uint64_t mod)
{
	uint64_t	res;

	res = to_sq % mod;
	res = (res * res) % mod;
	return (res);
}

uint64_t		ft_rapid_expo_mod(uint64_t nbr, uint64_t exp, uint64_t mod)
{
	if (!(exp))
		return (1);
	if (1 & exp)
		return ((nbr * ft_rapid_expo_mod(nbr, exp - 1, mod)) % mod);
	return (ft_sq_mod(ft_rapid_expo_mod(nbr, exp >> 1, mod), mod));
}

/*
** Test de primalite avec une incertitude de l'ordre de 4 ^ (-k)
*/

static int		ft_test_random(uint64_t to_test, uint64_t d, uint64_t r)
{
	uint64_t	i;
	uint64_t	tmp;

	i = 0;
	tmp = ft_random_range(2, to_test - 2);
	tmp = ft_rapid_expo_mod(tmp, d, to_test);
	if (tmp != 1 && tmp != to_test - 1)
	{
		while (++i < r && tmp != to_test - 1)
			tmp = (tmp * tmp) % to_test;
		if (i == r && tmp != to_test - 1)
			return (0);
	}
	return (1);
}

int				ft_miller_rabin(uint64_t to_test, uint64_t k)
{
	uint64_t	r;
	uint64_t	d;

	if (to_test <= 3 || !(1 & to_test))
		return (to_test == 2 || to_test == 3 ? 1 : 0);
	r = 0;
	d = to_test - 1;
	while (!(1 & d))
	{
		d >>= 1;
		r++;
	}
	while ((k--))
	{
		if (!(ft_test_random(to_test, d, r)))
			return (0);
	}
	return (1);
}
