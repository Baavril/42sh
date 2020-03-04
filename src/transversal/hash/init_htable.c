/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_htable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:12:19 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/12 15:32:29 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

t_htable		ft_init_htable(size_t entry_nbr, int e_table_type)
{
	t_htable	table;

	table.table_size = (entry_nbr * 100) / 70;
	table.big_prime = ft_get_prime(3 * table.table_size);
	table.ran_a = ft_get_ran(table.big_prime);
	table.ran_b = ft_get_ran(table.big_prime);
	table.entry_nbr = 0;
	table.data_type = e_table_type;
	table.table = (t_hlist **)ft_memalloc(
									sizeof(t_hlist *) * table.table_size);
	return (table);
}
