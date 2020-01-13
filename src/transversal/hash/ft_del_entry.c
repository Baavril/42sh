/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:13:48 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/13 21:44:40 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "htable.h"

static t_hlist		*ft_entry_relink_hash_index(t_hlist **lst, char *key_todel)
{
	t_hlist	*voyager;
	t_hlist	*tmp;

	tmp = NULL;
	voyager = *lst;
	if (!(ft_strcmp(key_todel, voyager->content->key)))
	{
		*lst = (*lst)->next;
		return (voyager);
	}
	while ((voyager->next))
	{
		if (!(ft_strcmp(key_todel, voyager->next->content->key)))
		{
			tmp = voyager->next;
			voyager->next = voyager->next->next;
			break ;
		}
		voyager = voyager->next;
	}
	return (tmp);
}

int					ft_del_entry(t_htable *htable, char *key_todel)
{
	size_t				index;
	t_hlist				*entry;
	t_hlist				*tmp;

	tmp = NULL;
	index = ft_hash(htable, key_todel);
	if ((entry = (t_hlist*)(htable->table[index])))
		tmp = ft_entry_relink_hash_index(&entry, key_todel);
	if (tmp)
	{
		ft_lstdelone((t_list**)(&tmp), ft_get_free(htable->data_type));
		htable->entry_nbr--;
		return (1);
	}
	return (0);
}
