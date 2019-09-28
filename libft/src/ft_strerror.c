/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:47:47 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/09 20:49:43 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_errno.h"

char	*ft_strerror(int errnum)
{
	if (errnum < g_sys_nerr)
	{
		g_errno = 0;
		return ((char*)g_sys_errlist[errnum]);
	}
	else
	{
		return ((char*)g_sys_errlist[g_sys_nerr]);
	}
}
