/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:54:10 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:23:33 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static __inline__ int	m0x07ff_utf8(wchar_t *wc)
{
	wchar_t	tmp;

	tmp = 0;
	tmp ^= ((*wc << 16) & ~0xFFC0FFFF);
	tmp ^= ((*wc << 18) & ~0xE0FFFFFF);
	tmp ^= 0xC0000000 | 0x800000;
	*wc = tmp;
	return ((int)*wc);
}

static __inline__ int	m0xffff_utf8(wchar_t *wc)
{
	*wc = ((*wc << 12) & ~0xF0FFFFFF) | ((*wc << 10) & ~0xFFC0FFFF)
		| ((*wc << 8) & ~0xFFFFC0FF);
	*wc ^= 0xE0000000 | 0x800000 | 0x8000;
	return ((int)*wc);
}

static __inline__ int	m0x10ffff_ut8(wchar_t *wc)
{
	*wc = ((*wc << 7) & ~0xF8FFFFFF) | ((*wc << 4) & ~0xFFC0FFFF)
		| ((*wc << 2) & ~0xFFFFC0FF) | (*wc & ~0xFFFFFFC0);
	*wc ^= 0xF0000000 | 0x800000 | 0x8000 | 0x80;
	return ((int)*wc);
}

int					utf8_encoder(wchar_t *wc)
{
	_Static_assert(sizeof(wchar_t) == 4,
			"System does not support 32bits wchar_t");
	if (*wc < 0)
		return (-1);
	else if (*wc <= 0x007F)
		return ((int)*wc);
	else if (*wc <= 0x07FF)
		return (m0x07ff_utf8(wc));
	else if (*wc <= 0xFFFF)
		return (m0xffff_utf8(wc));
	else if (*wc <= 0x10FFFF)
		return (m0x10ffff_ut8(wc));
	else
		return (-1);
}
