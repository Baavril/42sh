/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:28:14 by tgouedar          #+#    #+#             */
/*   Updated: 2019/09/28 13:34:27 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

const char	*ft_get_entry(const t_htable *htable, const char *key)
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
