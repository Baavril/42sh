/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:01:40 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/15 16:21:46 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

#include "prs_struct.h"
#include "specifiers.h"
#include "prefix.h"
#include "cast.h"
#include "format.h"

extern t_flags		g_flags;
extern t_prefix		g_prefix;
extern t_modifier	g_modifier;

void	ft_unbr(uintmax_t nb)
{
	reset_prefix();
	ft_cast_unbr(&nb);
	g_prefix.len = ft_unbrlen(nb);
	g_flags.hash = 0;
	g_flags.space = 0;
	g_flags.plus = 0;
	format(nb);
}

void	ft_upunbr(uintmax_t nb)
{
	reset_prefix();
	g_modifier.l = 1;
	g_modifier.h = 0;
	g_modifier.hh = 0;
	ft_cast_unbr(&nb);
	g_prefix.len = ft_unbrlen(nb);
	g_flags.hash = 0;
	g_flags.space = 0;
	g_flags.plus = 0;
	format(nb);
}
