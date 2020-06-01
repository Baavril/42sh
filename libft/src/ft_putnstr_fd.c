/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:27:41 by tgouedar          #+#    #+#             */
/*   Updated: 2020/06/01 15:30:56 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

void	ft_putnstr_fd(char const *s, size_t n, int fd)
{
	size_t len;

	len = ft_strlen(s);
	if (write(fd, s, n < len ? n : len) == -1)
	{
		perror(NULL);
	}
}
