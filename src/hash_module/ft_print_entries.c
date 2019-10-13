/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_entries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:23:01 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/13 04:04:24 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

static int			ft_cmp_entry(t_list *to_cmp1, t_list *to_cmp2)
{
	t_hlist		*entry1;
	t_hlist		*entry2;
	
	entry1 = (t_hlist*)to_cmp1;
	entry2 = (t_hlist*)to_cmp2;
	return (ft_strcmp(entry2->content->key, entry1->content->key));
}

static void		ft_print_entry(t_list *to_print)
{
	t_hlist		*entry;

	entry = (t_hlist*)to_print;
	ft_printf("%s=%s\n", entry->content->key, entry->content->value);
}

void			ft_print_sortentries(const t_htable *htable)
{
	t_list		*entries;

	entries = (t_list*)ft_lst_entries(htable);
	ft_lst_mergesort(&entries, &ft_cmp_entry);
	ft_lstiter(entries, &ft_print_entry);
	ft_lstdel(&entries, &ft_free_s_entry);
}
