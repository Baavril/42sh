/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:28:14 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/04 15:10:42 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

void		*ft_get_entry(const t_htable *htable, const char *key)
{
	size_t				index;
	t_hlist				*entry;
	t_entry				*content;

	index = ft_hash(htable, key);
	if ((entry = (t_hlist*)(htable->table[index])))
	{
		while ((entry))
		{
			content = (t_entry*)(entry->content);
			if (!(ft_strcmp(key, content->key)))
				return (content->value);
			entry = entry->next;
		}
	}
	return (NULL);
}
