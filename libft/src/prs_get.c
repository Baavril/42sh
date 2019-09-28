/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 12:17:11 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:23:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "prs_struct.h"
#include "specifiers.h"

extern t_ret		g_ret;
extern t_modifier	g_modifier;
extern t_options	g_options;

void					get_flags(const char *__restrict__ format
		, _Bool *__restrict__ specifier)
{
	if (!(format[g_ret.fmt_i] ^ '#'))
		g_flags.hash = 1;
	else if (!(format[g_ret.fmt_i] ^ '-'))
	{
		g_flags.minus = 1;
		g_flags.zero = 0;
	}
	else if (!(format[g_ret.fmt_i] ^ '0'))
		g_flags.zero = !(g_flags.minus) ? 1 : 0;
	else if (!(format[g_ret.fmt_i] ^ '+'))
	{
		g_flags.plus = 1;
		g_flags.space = 0;
	}
	else if (!(format[g_ret.fmt_i] ^ ' '))
		g_flags.space = !(g_flags.plus) ? 1 : 0;
	else if (!(format[g_ret.fmt_i] ^ '\''))
		g_flags.apost = 1;
	else
	{
		*specifier = 0;
		ft_chr(format[g_ret.fmt_i]);
	}
}

static __inline__ _Bool		get_additional_modifier(const char *__restrict__ format)
{
	if (!(format[g_ret.fmt_i] ^ 'j'))
	{
		g_modifier.j = 1;
		return (0);
	}
	else if (!(format[g_ret.fmt_i] ^ 't'))
	{
		g_modifier.t = 1;
		return (0);
	}
	else if (!(format[g_ret.fmt_i] ^ 'z'))
	{
		g_modifier.z = 1;
		return (0);
	}
	else if (!(format[g_ret.fmt_i] ^ 'L'))
	{
		g_modifier.upl = 1;
		return (0);
	}
	else
		return (1);
}

_Bool					get_modifier(const char *__restrict__ format)
{
	if (!(format[g_ret.fmt_i] ^ 'l'))
	{
		g_modifier.l = 1;
		if (!(format[g_ret.fmt_i + 1] ^ 'l'))
		{
			++g_ret.fmt_i;
			g_modifier.l = 0;
			g_modifier.ll = 1;
		}
		return (0);
	}
	else if (!(format[g_ret.fmt_i] ^ 'h'))
	{
		g_modifier.h = 1;
		if (!(format[g_ret.fmt_i + 1] ^ 'h'))
		{
			++g_ret.fmt_i;
			g_modifier.h = 0;
			g_modifier.hh = 1;
		}
		return (0);
	}
	else if (!(get_additional_modifier(format)))
		return (0);
	return (1);
}

void					ft_get_width_or_dollar(const char *__restrict__ str
		, _Bool dot)
{
	int	nbr;

	nbr = 0;
	while (str[g_ret.fmt_i] > 47 && str[g_ret.fmt_i] < 58)
	{
		nbr = nbr * 10 + (str[g_ret.fmt_i] ^ '0');
		++g_ret.fmt_i;
	}
	if (dot)
	{
		g_options.precision = nbr;
		--g_ret.fmt_i;
	}
	else if (!(str[g_ret.fmt_i] ^ '$'))
		g_options.val_dol = nbr;
	else
	{
		g_options.width = nbr;
		--g_ret.fmt_i;
	}
}

void					get_precision(const char *__restrict__ format, va_list ap)
{
	while (!(format[g_ret.fmt_i] ^ '.'))
		++g_ret.fmt_i;
	if (!(format[g_ret.fmt_i] ^ '*'))
	{
		g_options.precision = va_arg(ap, int);
		++g_options.i_ap;
	}
	else if (!((format[g_ret.fmt_i] & '0')) ^ '0')
	{
		if (format[g_ret.fmt_i] >= '0' && format[g_ret.fmt_i] <= '9')
			ft_get_width_or_dollar(format, 1);
		else
		{
			--g_ret.fmt_i;
			g_options.precision = 0;
		}
	}
}
