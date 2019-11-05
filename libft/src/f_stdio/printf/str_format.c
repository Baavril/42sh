/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:39:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:25:15 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "prs_struct.h"
#include "ft_expand_ret.h"
#include "prefix.h"
#include "ft_wchar.h"
#include "utf8.h"

extern _Bool		g_error;
extern t_flags		g_flags;
extern t_options	g_options;
extern t_modifier	g_modifier;
extern t_prefix		g_prefix;

static __inline__ void			ret_str(char *__restrict__ str)
{
	while (g_prefix.len)
	{
		g_ret.ret[++g_ret.i] = *str++;
		--g_options.width;
		--g_prefix.len;
	}
}

static __inline__ void			ret_wcs(wchar_t *__restrict__ wcs)
{
	wchar_t wc;

	while (g_prefix.len)
	{
		--g_options.width;
		wc = *wcs;
		utf8_encoder(&wc);
		if ((char)(wc >> 24))
			g_ret.ret[++g_ret.i] = (char)(wc >> 24);
		if ((char)(wc >> 16))
			g_ret.ret[++g_ret.i] = (char)(wc >> 16);
		if ((char)(wc >> 8))
			g_ret.ret[++g_ret.i] = (char)(wc >> 8);
		if ((char)wc)
			g_ret.ret[++g_ret.i] = (char)wc;
		g_prefix.len -= ft_ewcwidth(*wcs);
		++wcs;
	}
}

void						str_format(void *__restrict__ str)
{
	int	size;

	size = g_options.width < g_prefix.len ? g_prefix.len : g_options.width;
	if ((int)((unsigned int)(g_ret.i + size)) < -1 && (g_error = 1))
		return ;
	if (g_ret.i + size >= g_ret.max)
		ft_expand_ret(size);
	if (g_error)
		return ;
	while (!(g_flags.minus) && g_options.width - g_prefix.len > 0)
	{
		--g_options.width;
		g_ret.ret[++g_ret.i] = g_flags.zero ? '0' : ' ';
	}
	if (g_modifier.l)
		ret_wcs(str);
	else
		ret_str(str);
	while (g_flags.minus && g_options.width > 0)
	{
		--g_options.width;
		g_ret.ret[++g_ret.i] = ' ';
	}
}
