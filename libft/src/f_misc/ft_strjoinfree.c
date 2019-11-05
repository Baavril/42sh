/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 09:12:52 by bprunevi          #+#    #+#             */
/*   Updated: 2019/09/29 09:44:21 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*cpy;

	cpy = ft_strjoin(s1, s2);
	if (cpy)
	{
		free((void *)s1);
		free((void *)s2);
	}
	return (cpy);
}
