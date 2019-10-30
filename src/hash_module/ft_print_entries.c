/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_entries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:23:01 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/30 14:17:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

void			ft_print_sortentries(const t_htable *htable)
{
	t_list		*entries;
	int			table_type;

	table_type = htable->data_type;
	entries = (t_list*)ft_lst_entries(htable);
	ft_lst_mergesort(&entries, ft_get_lstcmp(table_type));
	ft_lstiter(entries, ft_get_lstprint(table_type));
	ft_lstdel(&entries, ft_get_free(table_type));
}
