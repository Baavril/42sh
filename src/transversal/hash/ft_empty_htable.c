/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty_htable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 21:53:29 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/23 15:12:21 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

void		ft_empty_htable(t_htable *htable)
{
	size_t		i;
	t_hlist		**table;

	i = 0;
	table = htable->table;
	while (i < htable->table_size)
	{
		if (table[i] != NULL)
			ft_lstdel((t_list**)(&(table[i])), ft_get_free(htable->data_type));
		i++;
	}
	htable->entry_nbr = 0;
}
