/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:54:14 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/18 12:16:45 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "prs_struct.h"

extern t_modifier	g_modifier;

void	ft_cast_unbr(uintmax_t *__restrict__ nb)
{
	if (g_modifier.hh)
		*nb = (unsigned char)(*nb);
	else if (g_modifier.h)
		*nb = (unsigned short)(*nb);
	else if (g_modifier.l)
		*nb = (unsigned long)(*nb);
	else if (g_modifier.ll)
		*nb = (unsigned long long)*nb;
	else if (g_modifier.j)
		*nb = (uintmax_t)(*nb);
	else if (g_modifier.t)
		*nb = (ptrdiff_t)(*nb);
	else if (g_modifier.z)
		*nb = (size_t)(*nb);
	else
		*nb = (unsigned int)(*nb);
}

void	ft_cast_nbr(intmax_t *__restrict__ nb)
{
	if (g_modifier.hh)
		*nb = (char)(*nb);
	else if (g_modifier.h)
		*nb = (short)(*nb);
	else if (g_modifier.l)
		*nb = (long)(*nb);
	else if (g_modifier.ll)
		*nb = (long long)*nb;
	else if (g_modifier.j)
		*nb = (intmax_t)(*nb);
	else if (g_modifier.t)
		*nb = (ptrdiff_t)(*nb);
	else if (g_modifier.z)
		*nb = (size_t)(*nb);
	else
		*nb = (int)(*nb);
}
