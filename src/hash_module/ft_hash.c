/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:59:47 by tgouedar          #+#    #+#             */
/*   Updated: 2019/09/27 16:21:03 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

static uint64_t	ft_pre_hash(const char *entry, uint64_t table_size)
{
	uint64_t		i;
	uint64_t		key;
	uint64_t		p_pow;

	i = 0;
	key = 0;
	p_pow = 1;
	while (entry[i])
	{
		key += (entry[i++] * p_pow) % table_size;
		p_pow = (p_pow * ALPH_PRIME) % table_size;
	}
	return (key);
}

uint64_t			ft_hash(const t_htable *htable, const char *entry)
{
	uint64_t		key;

	key = ft_pre_hash(entry, htable->table_size);
	key = (htable->ran_a * key + htable->ran_b) % htable->big_prime;
	key %= htable->table_size;
	return (key);
}
