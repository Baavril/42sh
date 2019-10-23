/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:00:54 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/23 18:44:29 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash_module.h"

void	ft_free_bash(void *to_free, size_t null)
{
	t_entry		*entry;

	entry = (t_entry*)to_free;
	(void)null;
	free(entry->key);
	free(((t_bash_hash*)(entry->value))->bin_path);
	free(entry->value);
	free(entry);
}

t_list		*ft_bash_lstcpy(t_list *elem)
{
	t_hlist			*new;
	t_bash_hash		*tmp;

	new = (t_hlist*)elem;
	new->content->key = ft_strdup(new->content->key);
	tmp = ft_memalloc(new->content->value_size);
	ft_memcpy(tmp, new->content->value, new->content->value_size);
	tmp->bin_path = ft_strdup(tmp->bin_path);
	new->content->value = tmp;
	return (elem);
}

void	ft_print_bash(t_list *to_print)
{
	t_bash_hash		*entry;
	char			*print_text;

	entry = ((t_hlist*)to_print)->content->value;
	if (entry->hit_value < 10000)
		print_text = "%4u    %s\n";
	else// if (entry->hit_value < 1000000)
		print_text = "%-8u%s\n";
	ft_printf(print_text, entry->hit_value, entry->bin_path);
}

void	ft_insert_bash(t_htable *htable, char *key,
												char *path, unsigned int hit)
{
	t_bash_hash		new;

	new.bin_path = path;
	new.hit_value = hit;
	ft_insert(htable, key, &new);
}
