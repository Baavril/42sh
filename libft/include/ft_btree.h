/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:11:02 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/23 18:25:15 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

struct s_btree
{
	void		*data;
	struct s_btree	*left;
	struct s_btree	*right;
};

struct s_btree	*btree_create_node(void *data);
void			btree_apply_prefix(struct s_btree *root, void (*applyf)(void *));
void			btree_apply_infix(struct s_btree *root, void (*applyf)(void *));
void			btree_apply_postfix(struct s_btree *root, void (*applyf)(void *));
void			btree_insert_data(struct s_btree **root, void *data, int (*cmpf)(void *, void *));
struct s_btree	*btree_search_data(struct s_btree *root, void *data_ref, int (*cmpf)(void *, void *));
void			btree_apply_by_level(struct s_btree *root, void (*applyf)(void *item, size_t current_level, size_t is_first_elem));
/*void		    btree_remove_data(struct s_btree **root, void *data_ref, int (*cmpf)(void *, void *), void (*del)(void *));
*/void			*btree_free_node(struct s_btree *node, void (*del)(void *));
size_t			btree_level_count(struct s_btree *root);
void			btree_delete(struct s_btree **root, void (*del)(void *));

#endif
