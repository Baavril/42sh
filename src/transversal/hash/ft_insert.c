/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:52:54 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/20 15:08:13 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "htable_type_dispatcher.h"
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
	htable->table = (t_hlist **)ft_memalloc(
										sizeof(t_hlist*) * htable->table_size);
	voyager = entries;
	while (voyager)
	{
		ft_insert(htable, voyager->content->key, voyager->content->value);
		voyager = voyager->next;
	}
	ft_lstdel((t_list**)&entries, ft_get_free(htable->data_type));
}

static int			ft_redefine_entry(t_hlist **list, char *key, int type)
{
	t_hlist		*voyager;
	t_hlist		*prev;

	if (!(voyager = *list))
		return (0);
	prev = *list;
	if (!(ft_strcmp(key, voyager->content->key)))
	{
		*list = voyager->next;
		ft_lstdelone((t_list**)&voyager, ft_get_free(type));
		return (1);
	}
	while (voyager->next)
	{
		voyager = voyager->next;
		if (!(ft_strcmp(key, voyager->content->key)))
		{
			prev->next = voyager->next;
			ft_lstdelone((t_list**)&voyager, ft_get_free(type));
			return (1);
		}
		prev = voyager;
	}
	return (0);
}

void				ft_insert(t_htable *htable, char *key, void *value)
{
	int				data_type;
	t_entry			content;
	t_hlist			*new_entry;
	t_hlist			**lst;
	t_ft_lstcpy		ft_cpy;

	data_type = htable->data_type;
	content.key = key;
	content.value_size = ft_get_value_size(htable->data_type, value);
	content.value = value;
	new_entry = (t_hlist*)ft_lstnew(&content, sizeof(content));
	ft_cpy = ft_get_lstcpy(data_type);
	ft_cpy((t_list*)new_entry);
	lst = &(htable->table[ft_hash(htable, new_entry->content->key)]);
	if (!(ft_redefine_entry(lst, key, htable->data_type)))
		(htable->entry_nbr)++;
	ft_lstadd((t_list**)lst, (t_list*)new_entry);
	if (htable->entry_nbr * 100 / htable->table_size > 70)
		ft_resize_htable(htable);
}
