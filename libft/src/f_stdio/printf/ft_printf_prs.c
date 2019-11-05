/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 12:39:43 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 15:24:32 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdarg.h>

#include "prs_struct.h"
#include "prs_get.h"
#include "wrapper.h"
#include "dispatcher.h"
#include "specifiers.h"
#include "ft_expand_ret.h"

static va_list	g_ap_origin;
t_ret			g_ret;
t_modifier		g_modifier =
{.hh = 0, .h = 0, .l = 0, .ll = 0, .j = 0, .t = 0, .z = 0, .upl = 0};
t_options		g_options =
{.width = -1, .precision = -1, .i_ap = 0, .val_dol = 0};
t_flags			g_flags =
{.hash = 0, .zero = 0, .minus = 0, .space = 0, .plus = 0, .apost = 0};
_Bool			g_error = 0;

static __inline__ void	reset_globals(void)
{
	g_options.width = -1;
	g_options.precision = -1;
	g_options.val_dol = 0;
	g_flags.hash = 0;
	g_flags.zero = 0;
	g_flags.minus = 0;
	g_flags.space = 0;
	g_flags.plus = 0;
	g_flags.apost = 0;
	g_modifier.hh = 0;
	g_modifier.h = 0;
	g_modifier.l = 0;
	g_modifier.ll = 0;
	g_modifier.j = 0;
	g_modifier.t = 0;
	g_modifier.z = 0;
	g_modifier.upl = 0;
}

static __inline__ _Bool	get_fwpm(const char *__restrict__ format, va_list ap
		, _Bool *__restrict__ specifier)
{
	if (format[g_ret.fmt_i] > '0' && format[g_ret.fmt_i] <= '9')
	{
		ft_get_width_or_dollar(format, 0);
		return (1);
	}
	else if (!(format[g_ret.fmt_i] ^ '.'))
	{
		get_precision(format, ap);
		return (1);
	}
	else if (!(format[g_ret.fmt_i] ^ '*'))
	{
		g_options.width = va_arg(ap, int);
		++g_options.i_ap;
		return (1);
	}
	else if (!((format[g_ret.fmt_i] & ' ') ^ ' ')
			&& format[g_ret.fmt_i] < '1')
	{
		get_flags(format, specifier);
		return (1);
	}
	else
		return (0);
}

static __inline__ _Bool	prs_specifier(const char *__restrict__ format, va_list ap)
{
	void	*(*f)();
	_Bool	specifier;

	while (!(format[g_ret.fmt_i] ^ '%'))
	{
		reset_globals();
		specifier = 1;
		while (format[++g_ret.fmt_i] && specifier)
		{
			if (get_fwpm(format, ap, &specifier))
				continue ;
			else if ((f = dispatcher(format[g_ret.fmt_i])))
			{
				specifier = 0;
				if (g_options.val_dol)
					__va_copy(ap, g_ap_origin);
				wrapper(f, ap);
			}
			else if (specifier)
				if (get_modifier(format) && !(specifier = 0))
					ft_chr(format[g_ret.fmt_i]);
		}
	}
	return (0);
}

int					printf_prs(const char *__restrict__ format, va_list ap)
{
	g_ret.fmt_i = 0;
	__va_copy(g_ap_origin, ap);
	if (!(format))
		return (-1);
	while (format[g_ret.fmt_i] && !(prs_specifier(format, ap)))
	{
		if (g_error)
		{
			g_error = 0;
			return (-1);
		}
		if (!(format[g_ret.fmt_i]))
			break ;
		while (g_ret.i + 1 >= g_ret.max)
			ft_expand_ret(1);
		++g_ret.i;
		g_ret.ret[g_ret.i] = format[g_ret.fmt_i];
		++g_ret.fmt_i;
	}
	return (g_ret.i + 1);
}
