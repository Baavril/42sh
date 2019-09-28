/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 12:47:59 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 14:45:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "specifiers.h"
#include "prs_struct.h"

extern t_options	g_options;

void	wrapper(void *(*f)(), va_list ap)
{
	int	i;
	int	rubbish;

	i = 1;
	while (i < g_options.val_dol)
	{
		rubbish = va_arg(ap, int);
		(void)rubbish;
		++i;
	}
	if (f == (void*)&ft_double)
		f(ap);
	else
		f(va_arg(ap, __typeof__(ap)));
	++g_options.i_ap;
}
