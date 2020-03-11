/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:39:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/16 14:18:21 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

#include "prs_struct.h"
#include "prefix.h"
#include "cast.h"
#include "format.h"

extern t_flags		g_flags;
extern t_options	g_options;
extern t_prefix		g_prefix;
extern t_modifier	g_modifier;

void							ft_octal(uintmax_t nb)
{
	reset_prefix();
	ft_cast_unbr(&nb);
	g_prefix.base = 8;
	g_flags.plus = 0;
	if (g_flags.hash && (!(g_options.precision) || nb > 0))
	{
		g_prefix.size = 1;
		g_prefix.prefix = "0";
	}
	g_prefix.len = ft_unbrlen((uintmax_t)nb);
	if (g_options.precision > g_prefix.len)
		g_prefix.size = 0;
	format(nb);
}

void							ft_upoc(uintmax_t nb)
{
	g_modifier.l = 1;
	g_modifier.h = 0;
	g_modifier.hh = 0;
	g_flags.space = 0;
	g_flags.plus = 0;
	ft_octal(nb);
}
