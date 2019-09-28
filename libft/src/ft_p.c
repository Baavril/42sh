/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:00:19 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/07 14:14:53 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

#include "prs_struct.h"
#include "prefix.h"
#include "cast.h"
#include "format.h"

extern t_flags		g_flags;
extern t_modifier	g_modifier;

void	ft_p(void *__restrict__ ptr)
{
	uintmax_t p_ptr;

	p_ptr = (uintmax_t)ptr;
	g_flags.hash = 1;
	g_flags.apost = 0;
	if (sizeof(void*) == 8)
		g_modifier.l = 1;
	reset_prefix();
	ft_cast_unbr(&p_ptr);
	g_prefix.base = 16;
	g_flags.plus = 0;
	g_flags.apost = 0;
	if (g_flags.hash)
	{
		g_prefix.size = 2;
		g_prefix.prefix = "0x";
	}
	g_prefix.ch_base = "0123456789abcdef";
	g_prefix.len = ft_unbrlen(p_ptr);
	format(p_ptr);
}
