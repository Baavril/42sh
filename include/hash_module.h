/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_module.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:31:23 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/23 18:26:25 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MODULE_H
# define HASH_MODULE_H

# include "htable.h"

# define AVG_BIN_NBR		1500
# define DEF_SIZE			200
# define HIT				1
# define NO_HIT				0

t_htable			ft_init_htable(size_t entry_nbr, int e_data_type);
void				ft_insert(t_htable *htable, char *key, void *value);
const void			*ft_get_entry(const t_htable *htable, const char *key);
void				ft_iter_htable(t_htable *htable, t_ft_list to_apply);
void				ft_print_sortentries(const t_htable *htable);
void				ft_free_htable(t_htable *table);
void				ft_empty_htable(t_htable *htable);
void				ft_insert_bash(t_htable *htable, char *key,
												char *path, unsigned int hit);
void				ft_hash_path(t_htable *bin_table, char *path);

#endif
