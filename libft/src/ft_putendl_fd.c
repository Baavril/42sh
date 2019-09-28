/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 08:19:06 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 16:47:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	if (s && *s)
	{
		if (write(fd, s, ft_strlen(s)) == -1)
		{
			perror(NULL);
		}
	}
	if (s)
	{
		if (write(fd, "\n", sizeof(char)) == -1)
		{
			perror(NULL);
		}
	}
}
