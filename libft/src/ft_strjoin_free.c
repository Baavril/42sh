/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 09:12:52 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/17 15:17:59 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char *s1, char *s2, int opt)
{
	char	*cpy;

	cpy = ft_strjoin(s1, s2);
	if (cpy)
	{
		if (opt == 1 || opt == 3)
			free((void *)s1);
		if (opt == 2 || opt == 3)
			free((void *)s2);
	}
	return (cpy);
}
