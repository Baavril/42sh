/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 08:16:07 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 16:46:04 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (s && *s)
	{
		if (write(fd, s, ft_strlen(s)) == -1)
		{
			perror(NULL);
		}
	}
}
