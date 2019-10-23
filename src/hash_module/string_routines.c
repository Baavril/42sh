/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:14:45 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/23 18:02:58 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "htable.h"

t_list		*ft_string_lstcpy(t_list *elem)
{
	t_hlist		*new;

	new = (t_hlist*)elem;
	new->content->key = ft_strdup(new->content->key);
	new->content->value = ft_strdup(new->content->value);
	return (elem);
}

void					ft_print_string(t_list *to_print)
{
	t_hlist		*entry;

	entry = (t_hlist*)to_print;
	ft_printf("%s=%s\n", entry->content->key, entry->content->value);
}

void					ft_free_string(void *to_free, size_t null)
{
	t_entry		*entry;

	entry = (t_entry*)to_free;
	(void)null;
	free(entry->key);
	free(entry->value);
	free(entry);
}
