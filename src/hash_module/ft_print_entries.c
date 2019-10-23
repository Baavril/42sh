/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_entries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:23:01 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/23 15:06:16 by tgouedar         ###   ########.fr       */
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

void			ft_print_sortentries(const t_htable *htable)
{
	t_list		*entries;

	ft_putendl("\nFT_PRINT_ENTRY\n");
	entries = (t_list*)ft_lst_entries(htable);
	ft_lst_mergesort(&entries, &ft_cmp_entry);
	ft_lstiter(entries, ft_get_lstprint(htable->data_type));
	ft_lstdel(&entries, ft_get_free(htable->data_type));
}
