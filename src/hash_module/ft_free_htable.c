/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_htable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:48:25 by tgouedar          #+#    #+#             */
/*   Updated: 2019/09/30 18:04:44 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "htable.h"

static void			ft_free_s_entry(void *to_free, size_t null)
{
	t_entry		*entry;

	entry = (t_entry*)to_free;
	(void)null;
	free(entry->key);
	free(entry->value);
	free(&entry->key);
	free(&entry->value);
}

void				ft_free_htable(t_htable *table)
{
	uint64_t	i;
	t_list		*voyager;

	i = 0;
	while (i < table->table_size)
	{
		voyager = (table->table)[i];
		if (voyager)
			ft_lstdel(&voyager, &ft_free_s_entry);
		i++;
	}
	free(table->table);
}
