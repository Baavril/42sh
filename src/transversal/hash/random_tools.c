/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:48:28 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/13 21:52:08 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "htable.h"

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
	return (min + (ft_random_get() % (max - min)));
}

uint64_t			ft_get_ran(uint64_t mod)
{
	uint64_t	res;

	res = 0;
	while (!(res % mod))
		res = ft_random_get();
	return (res % mod);
}

uint64_t			ft_get_prime(uint64_t min)
{
	uint64_t	res;

	res = 0;
	while (!(ft_miller_rabin(res, GOOD_ENOUGH)))
		res = min + ft_random_get();
	return (res);
}
