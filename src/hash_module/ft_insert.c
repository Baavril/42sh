/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:52:54 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/13 05:02:21 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash_module.h"

static void			ft_resize_htable(t_htable *htable)
{
	t_hlist		*entries;
	t_hlist		*voyager;

	entries = ft_lst_entries(htable);
	ft_empty_htable(htable);
	htable->table_size *= 2;
	htable->big_prime = ft_get_prime(3 * htable->table_size);
	htable->ran_a = ft_get_ran(htable->big_prime);
	htable->ran_b = ft_get_ran(htable->big_prime);
	free(htable->table);
	/*ft_check_memory(*/htable->table = (t_hlist **)ft_memalloc(sizeof(t_hlist *)
														* htable->table_size);
	voyager = entries;
	while (voyager)
	{
		ft_insert(htable, voyager->content->key, voyager->content->value);
		voyager = voyager->next;
	}
	ft_lstdel((t_list**)&entries, &ft_free_s_entry);
}

void				ft_insert(t_htable *htable, char *key, char *value)
{
	size_t		index;
	t_entry		content;
	t_hlist		*new_entry;

	content.key = ft_strdup(key);
	content.value = ft_strdup(value);
	/*ft_check_memory(*/new_entry = (t_hlist*)ft_lstnew(&content, sizeof(content));
	index = ft_hash(htable, key);
	ft_lstadd((t_list**)&(htable->table[index]), (t_list*)new_entry);
	(htable->entry_nbr)++;
	if (htable->entry_nbr * 100 / htable->table_size > 70)
		ft_resize_htable(htable);
}
