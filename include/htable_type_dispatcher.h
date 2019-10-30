/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable_type_dispatcher.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:11:10 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/30 14:17:32 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABLE_TYPE_DISPATCHER_H
# define HTABLE_TYPE_DISPATCHER_H

# include "htable.h"

enum	e_table_type
{
	e_string_entries,
	e_bash_entries
};

typedef struct			s_htable_type
{
	t_ft_free			ft_free;
	t_ft_list			ft_print;
	t_ft_lstcpy			ft_value_cpy;
	t_ft_cmp_entries	ft_cmp;
	size_t				value_size;
}						t_htable_type;

#endif
