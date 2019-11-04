/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:13:48 by tgouedar          #+#    #+#             */
/*   Updated: 2019/11/04 15:17:38 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "htable.h"

int		ft_del_entry(t_htable *htable, char *key_todel)
{
	size_t				index;
	t_hlist				*entry;
	t_hlist				*tmp;

	tmp = NULL;
	index = ft_hash(htable, key_todel);
	if ((entry = (t_hlist*)(htable->table[index])))
	{
		if (!(ft_strcmp(key_todel, entry->content->key)))
		{
			tmp = entry;
			htable->table[index] = entry->next;
		}
		while ((entry->next))
		{
			if (!(ft_strcmp(key_todel, entry->next->content->key)))
			{
				tmp = entry->next;
				entry->next = entry->next->next;
				break ;
			}
			entry = entry->next;
		}
	}
	if (tmp)
	{
		ft_lstdelone((t_list**)(&tmp), ft_get_free(htable->data_type));
		htable->entry_nbr--;
		return (1);
	}
	return (0);
}
