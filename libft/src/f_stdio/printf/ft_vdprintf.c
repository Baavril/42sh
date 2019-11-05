/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:51:19 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 16:46:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_vasprintf.h"
#include "libft.h"

int	ft_vdprintf(int fd, const char *__restrict__ format, va_list ap)
{
	char	*str;
	int		ret;

	ret = ft_vasprintf(&str, format, ap);
	if (ret != -1 && str)
	{
		if (write(fd, str, ret) == -1)
		{
			perror(NULL);
		}
	}
	ft_memdel((void**)&str);
	return (ret);
}
