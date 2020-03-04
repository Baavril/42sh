/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synt_const.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:51:41 by bprunevi          #+#    #+#             */
/*   Updated: 2019/07/21 11:54:26 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNT_CONST_H
# define SYNT_CONST_H

struct	s_operator
{
	char	*gram_op;
};

extern const struct s_operator	g_operator[];

#endif
