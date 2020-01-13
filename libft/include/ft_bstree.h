/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:11:02 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:58:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSTREE_H
# define FT_BSTREE_H

# include "ft_btree.h"

void		bstree_remove_data(struct s_btree **root, void *data_ref,
							int (*cmpf)(void *, void *), void (*del)(void *));

#endif
