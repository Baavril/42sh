/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:39:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/15 18:24:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

#include "prs_struct.h"
#include "prefix.h"
#include "cast.h"
#include "format.h"

extern t_flags		g_flags;
extern t_prefix		g_prefix;

void							ft_lhexa(uintmax_t nb)
{
	reset_prefix();
	ft_cast_unbr(&nb);
	g_prefix.base = 16;
	g_flags.plus = 0;
	g_flags.apost = 0;
	if (g_flags.hash && nb > 0)
	{
		g_prefix.size = 2;
		g_prefix.prefix = "0x";
	}
	g_prefix.ch_base = "0123456789abcdef";
	g_prefix.len = ft_unbrlen((uintmax_t)nb);
	format(nb);
}

void							ft_uhexa(uintmax_t nb)
{
	reset_prefix();
	ft_cast_unbr(&nb);
	g_prefix.base = 16;
	g_flags.plus = 0;
	g_flags.apost = 0;
	if (g_flags.hash && nb > 0)
	{
		g_prefix.size = 2;
		g_prefix.prefix = "0X";
	}
	g_prefix.len = ft_unbrlen((uintmax_t)nb);
	format(nb);
}
