/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_htable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:12:19 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/13 04:57:44 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

//#include "un header possedant une fonction ft_check_memory qui verifie le retour de malloc"

t_htable		ft_init_htable(size_t entry_nbr)
{
	t_htable	table;

	table.table_size = (entry_nbr * 100) / 70;
	table.big_prime = ft_get_prime(3 * table.table_size);
	table.ran_a = ft_get_ran(table.big_prime);
	table.ran_b = ft_get_ran(table.big_prime);
	table.entry_nbr = 0;
	/*ft_check_memory(*/table.table = (t_hlist **)ft_memalloc(sizeof(t_hlist *)
														* table.table_size);
	return (table);
}
