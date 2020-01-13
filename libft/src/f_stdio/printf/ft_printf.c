/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:27:49 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 14:15:41 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "ft_vdprintf.h"

int		ft_printf(const char *restrict format, ...)
{
	va_list ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(STDOUT_FILENO, format, ap);
	va_end(ap);
	return (ret);
}
