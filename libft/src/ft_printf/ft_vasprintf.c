/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:13:29 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/07 14:16:04 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "ft_printf_prs.h"
#include "prs_struct.h"
#include "libft.h"

int	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	extern t_ret	g_ret;
	int				parse_ret;

	g_ret.max = 128;
	g_ret.i = -1;
	if (!(*ret = (char*)ft_memalloc(sizeof(**ret) * 128 + 1)))
		return (-1);
	g_ret.ret = *ret;
	if (((parse_ret = printf_prs(format, ap)) == -1))
	{
		*ret = g_ret.ret;
		return (-1);
	}
	*ret = g_ret.ret;
	return (parse_ret);
}
