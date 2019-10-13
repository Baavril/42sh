/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corps_fini_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:56:53 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/12 23:06:51 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "htable.h"
#include <stdio.h>

unsigned int		ft_random_get(void)
{
	static unsigned int		nums[LIST_SIZE];
	static unsigned int		curr = 0;
	int						fd;

	if (curr % LIST_SIZE == 0)
	{
		curr = 0;
		fd = open("/dev/random", O_RDONLY);
		read(fd, nums, sizeof(unsigned int) * LIST_SIZE);
		close(fd);
	}
	return (nums[curr++]);
}

unsigned int		ft_random_range(unsigned int min, unsigned int max)
{
	return (min + (ft_random_get() % max));
}

uint64_t		ft_get_prime(uint64_t min)
{
	uint64_t	res;

	res = 0;
	while (!(ft_miller_rabin(res, GOOD_ENOUGH)))
		res = min + ft_random_get();
	return (res);
}

uint64_t		ft_get_ran(uint64_t mod)
{
	uint64_t	res;

	res = 0;
	while (!(res % mod))
		res = ft_random_get();
	return (res % mod);
}

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

/*int				ft_sqrt(uint64_t nbr)
{
	uint64_t	res;

	res = 2;
	while (res * res < nbr)
		res++;
	return (res);
}

uint64_t		ft_eratosthene(uint64_t nbr)
{
	uint64_t	sqrt;
	uint64_t	i;

	if (nbr <= 3 || !(1 & nbr))
		return (nbr == 2 || nbr == 3 ? 1 : 0);
	i = 3;
	sqrt = ft_sqrt(nbr);
	while (i <= sqrt)
	{
		if (!(nbr % i))
			return (0);
		i += 2;
	}
	return (1);
}*/

/* Test de primalite avec une incertitude de l'ordre de 4 ^ (-k) */

int				ft_miller_rabin(uint64_t to_test, uint64_t k)
{
	uint64_t	i;
	uint64_t	r;
	uint64_t	d;
	uint64_t	tmp;

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
		tmp = ft_random_range(2, to_test - 2);
		tmp = ft_rapid_expo_mod(tmp, d, to_test);
		if (tmp != 1 && tmp != to_test - 1)
		{
			i = 0;
			while (++i < r && tmp != to_test - 1)
				tmp = (tmp * tmp) % to_test;
			if (i == r && tmp != to_test - 1)
				return (0);
		}
	}
	return (1);
}
