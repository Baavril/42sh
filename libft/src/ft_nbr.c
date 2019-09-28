/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:39:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/15 19:16:29 by abarthel         ###   ########.fr       */
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
extern t_modifier	g_modifier;

void							ft_nbr(intmax_t nb)
{
	reset_prefix();
	ft_cast_nbr(&nb);
	g_prefix.len = ft_nbrlen(nb);
	g_flags.hash = 0;
	if (nb < 0)
	{
		g_prefix.size = 1;
		g_prefix.neg = 1;
		g_prefix.prefix = "-";
	}
	else if (g_flags.plus)
	{
		g_prefix.size = 1;
		g_prefix.prefix = "+";
	}
	else if (g_flags.space)
	{
		g_prefix.size = 1;
		g_prefix.prefix = " ";
	}
	format(nb < 0 ? nb * -1 : nb);
}

void							ft_upnbr(intmax_t nb)
{
	g_modifier.l = 1;
	g_modifier.h = 0;
	g_modifier.hh = 0;
	g_flags.hash = 0;
	g_flags.space = 0;
	g_flags.plus = 0;
	ft_nbr(nb);
}
