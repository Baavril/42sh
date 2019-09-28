/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:39:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:24:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

#include "prs_struct.h"
#include "ft_expand_ret.h"
#include "prefix.h"

extern _Bool		g_error;
extern t_flags		g_flags;
extern t_options	g_options;
extern t_prefix		g_prefix;

unsigned short		ft_nbrlen(intmax_t nb)
{
	intmax_t		rest;
	unsigned short	len;

	len = 0;
	rest = nb;
	while (rest)
	{
		++len;
		rest = (rest - (rest % g_prefix.base)) / g_prefix.base;
	}
	if (g_flags.apost)
		len += !(len % 3) ? len / 3 - 1 : len / 3;
	return (len > 0 ? len : 1);
}

unsigned short		ft_unbrlen(uintmax_t nb)
{
	uintmax_t		rest;
	unsigned short	len;

	len = 0;
	rest = nb;
	while (rest)
	{
		++len;
		rest = (rest - (rest % g_prefix.base)) / g_prefix.base;
	}
	if (g_flags.apost)
		len += !(len % 3) ? len / 3 - 1 : len / 3;
	return (len > 0 ? len : 1);
}

static __inline__ void	ret_nbr(uintmax_t nb, short len)
{
	int	mod;

	g_ret.i += len;
	mod = 0;
	while (len--)
	{
		++mod;
		if (g_flags.apost && !(mod % 4))
			g_ret.ret[g_ret.i] = *(g_prefix.lc->thousands_sep);
		else
		{
			g_ret.ret[g_ret.i] = g_prefix.ch_base[nb % g_prefix.base];
			nb = (nb - (nb % g_prefix.base)) / g_prefix.base;
		}
		--g_ret.i;
	}
}

static __inline__ void	width_precision(void)
{
	while (!(g_flags.zero) && !(g_flags.minus) && g_options.width - g_prefix.len
			- g_prefix.size > 0)
	{
		if (g_options.width - g_options.precision
					- g_prefix.size <= 0)
			break ;
		--g_options.width;
		g_ret.ret[++g_ret.i] = ' ';
	}
	if (g_prefix.size)
		while (*g_prefix.prefix)
		{
			g_ret.ret[++g_ret.i] = *g_prefix.prefix;
			++g_prefix.prefix;
		}
	if (g_flags.zero)
		g_options.precision = g_flags.plus | g_flags.hash | g_flags.space
			| g_prefix.neg ? g_options.width - g_prefix.size : g_options.width;
	while (g_options.precision - g_prefix.len > 0)
	{
		g_ret.ret[++g_ret.i] = '0';
		--g_options.precision;
		--g_options.width;
	}
}

extern void			format(uintmax_t nb)
{
	int	z;

	g_flags.zero = g_options.precision != -1 ? 0 : g_flags.zero;
	g_prefix.len = !(g_options.precision) && !(nb) ? 0 : g_prefix.len;
	z = g_prefix.len > g_options.precision ? g_prefix.len : g_options.precision;
	z = z > g_options.width ? g_prefix.len : g_options.width;
	z += g_prefix.size;
	if ((int)((unsigned int)(g_ret.i + z)) < -1 && (g_error = 1))
		return ;
	if (g_ret.i + z >= g_ret.max)
		ft_expand_ret(z);
	if (g_error)
		return ;
	width_precision();
	ret_nbr(nb, g_prefix.len);
	g_ret.i += g_prefix.len;
	z = g_options.width - g_prefix.len;
	while (g_flags.minus && g_options.width - g_prefix.len - g_prefix.size > 0)
	{
		--g_options.width;
		g_ret.ret[++g_ret.i] = ' ';
		if (g_options.width == g_prefix.len && (g_flags.plus || g_flags.hash
					|| g_flags.space || g_prefix.neg))
			g_ret.i -= g_prefix.size;
	}
}
