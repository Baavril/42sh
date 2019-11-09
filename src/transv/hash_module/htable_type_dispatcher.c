/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable_type_dispatcher.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:08:48 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/30 14:17:36 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "htable_type_dispatcher.h"

t_htable_type		g_htype[] =
{
	{&ft_free_string, &ft_print_string, &ft_string_lstcpy, &ft_cmp_entry_key, 0},
	{&ft_free_bash, &ft_print_bash, &ft_bash_lstcpy, &ft_bash_cmp, sizeof(t_bash_hash)}
};

t_ft_free			ft_get_free(int e_table_type)
{
	return (g_htype[e_table_type].ft_free);
}

t_ft_lstcpy			ft_get_lstcpy(int e_table_type)
{
	return (g_htype[e_table_type].ft_value_cpy);
}

t_ft_list			ft_get_lstprint(int e_table_type)
{
	return (g_htype[e_table_type].ft_print);
}

t_ft_cmp_entries	ft_get_lstcmp(int e_table_type)
{
	return (g_htype[e_table_type].ft_cmp);
}

size_t				ft_get_value_size(int e_table_type, void *value)
{
	if (e_table_type == e_string_entries)
		return (ft_strlen(value) + 1);
	return (g_htype[e_table_type].value_size);
}
