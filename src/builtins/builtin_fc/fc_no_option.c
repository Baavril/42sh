/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_no_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:44:11 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/15 16:48:09 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

extern int		g_arg;

int			ft_fc(char **option)
{
	(void)option;
	ft_printf("fc\n");
	return (1);
}
