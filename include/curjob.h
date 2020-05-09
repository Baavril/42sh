/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curjob.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:31:37 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/08 16:37:31 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURJOB_H
# define CURJOB_H
# include "libft.h"

typedef int		(*t_flist)(t_elem left, t_elem right);

int				curjob_add(t_node *node);
int				curjob_cat(char *str);

#endif
