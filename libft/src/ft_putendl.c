/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 07:05:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 16:47:18 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

void	ft_putendl(char const *s)
{
	if (s && *s)
	{
		if (write(STDOUT_FILENO, s, ft_strlen(s)) == -1)
		{
			perror(NULL);
		}
	}
	if (s)
	{
		if (write(STDOUT_FILENO, "\n", sizeof(char)) == -1)
		{
			perror(NULL);
		}
	}
}
