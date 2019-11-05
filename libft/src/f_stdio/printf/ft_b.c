/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:00:19 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/07 14:13:30 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "prs_struct.h"
#include "specifiers.h"
#include "prefix.h"
#include "format.h"

extern t_flags		g_flags;
extern t_modifier	g_modifier;
extern t_options	g_options;
extern t_prefix		g_prefix;

static __inline__ size_t	ft_type_len(void)
{
	if (g_modifier.hh)
		return (sizeof(char) * 8);
	else if (g_modifier.h)
		return (sizeof(short) * 8);
	else if (g_modifier.l)
		return (sizeof(long) * 8);
	else if (g_modifier.ll)
		return (sizeof(long long) * 8);
	else if (g_modifier.j)
		return (sizeof(intmax_t) * 8);
	else if (g_modifier.t)
		return (sizeof(ptrdiff_t) * 8);
	else if (g_modifier.z)
		return (sizeof(size_t) * 8);
	else
		return (sizeof(int) * 8);
}

void					ft_b(uintmax_t nb)
{
	reset_prefix();
	g_prefix.base = 2;
	g_flags.plus = 0;
	g_flags.zero = 0;
	if (g_flags.hash)
	{
		g_prefix.size = 2;
		g_prefix.prefix = "0b";
	}
	g_options.precision = 0;
	g_prefix.len = ft_type_len();
	format(nb);
}
