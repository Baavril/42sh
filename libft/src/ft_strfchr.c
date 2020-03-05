/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:49:43 by yberramd          #+#    #+#             */
/*   Updated: 2020/01/15 16:33:10 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strfchr(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 && !str2)
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] && str2)
		return (0);
	return (1);
}
