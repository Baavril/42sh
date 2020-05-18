/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curjob.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:31:37 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/10 14:56:53 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURJOB_H
# define CURJOB_H

# include "parser.h"
# include "libft.h"

typedef int		(*t_flist)(t_elem left, t_elem right);

int				curjob_add(t_node *node);
int				curjob_cat(char *str);

#endif
