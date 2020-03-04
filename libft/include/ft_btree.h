/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:11:02 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/05 15:02:24 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include <stdlib.h>

typedef struct		s_btree
{
	void			*data;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

t_btree				*btree_create_node(void *data);
void				btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void				btree_apply_infix(t_btree *root, void (*applyf)(void *));
void				btree_apply_postfix(t_btree *root, void (*applyf)(void *));
void				btree_insert_data(t_btree **root, void *data,
												int (*cmpf)(void *, void *));
t_btree				*btree_search_data(t_btree *root, void *data_ref,
												int (*cmpf)(void *, void *));
void				btree_apply_by_level(t_btree *root,
										void (*applyf)(void *, size_t, size_t));
void				*btree_free_node(t_btree *node, void (*del)(void *));
size_t				btree_level_count(t_btree *root);
void				btree_delete(t_btree **root, void (*del)(void *));

#endif
