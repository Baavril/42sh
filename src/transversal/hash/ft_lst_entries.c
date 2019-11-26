/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_entries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:02:05 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/30 13:52:51 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

t_hlist		*ft_lst_entries(const t_htable *htable)
{
	size_t		i;
	t_hlist		**table;
	t_hlist		*entries;

	i = 0;
	entries = NULL;
	table = htable->table;
	while (i < htable->table_size)
	{
		if (table[i])
			ft_lstadd((t_list**)&entries, ft_lstmap((t_list*)(table[i]),
											ft_get_lstcpy(htable->data_type)));
		i++;
	}
	return (entries);
}
