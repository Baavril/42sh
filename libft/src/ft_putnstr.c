/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:09:31 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/18 18:13:05 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

void	ft_putnstr(char const *s, size_t n)
{
	size_t len;

	len = ft_strlen(s);
	if (write(STDOUT_FILENO, s, n < len ? n : len) == -1)
	{
		perror(NULL);
	}
}
