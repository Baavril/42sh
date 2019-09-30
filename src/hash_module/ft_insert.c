/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:52:54 by tgouedar          #+#    #+#             */
/*   Updated: 2019/09/28 13:41:15 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

void		ft_insert(t_htable *htable, char *key, char *value)
{
	size_t		index;
	t_entry		content;
	t_list		*new_entry;

	content.key = ft_strdup(key);
	content.value = ft_strdup(value);
	/*ft_check_memory(*/new_entry = ft_lstnew(&content, sizeof(content));
	index = ft_hash(htable, key);
	ft_lstadd(&(htable->table[index]), new_entry);
	(htable->entry_nbr)++;
//	if (htable->entry_nbr * 100 / htable->table_size > 70)
//		resize_htable(t_htable);
}
