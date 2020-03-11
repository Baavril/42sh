/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:46:06 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/09 21:00:12 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "ft_errno.h"

void	ft_perror(const char *s)
{
	if (!s)
	{
		if (g_errno < g_sys_nerr)
			ft_dprintf(STDERR_FILENO, "%s\n", ft_strerror(g_errno));
		else
			ft_dprintf(STDERR_FILENO, "%s: %d\n",\
					ft_strerror(g_errno), g_errno);
	}
	else
	{
		if (g_errno < g_sys_nerr)
			ft_dprintf(STDERR_FILENO, "%s: %s\n", s, ft_strerror(g_errno));
		else
			ft_dprintf(STDERR_FILENO, "%s: %s: %d\n",\
					s, ft_strerror(g_errno), g_errno);
	}
}
