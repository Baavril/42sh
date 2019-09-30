/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_module.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:31:23 by tgouedar          #+#    #+#             */
/*   Updated: 2019/09/30 17:21:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MODULE_H
# define HASH_MODULE_H

#include "htable.h"

# define AVG_BIN_NBR		1500
# define DEF_SIZE			200

t_htable			ft_init_htable(size_t entry_nbr);
void				ft_insert(t_htable * htable, char *key, char *value);
const char			*ft_get_entry(const t_htable *htable, const char *key);
void				ft_hash_path(t_htable *bin_table, char *path);
void				ft_free_htable(t_htable *table);

#endif
