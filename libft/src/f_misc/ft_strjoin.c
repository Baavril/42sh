/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:48:12 by abarthel          #+#    #+#             */
/*   Updated: 2019/01/29 12:49:37 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cpy;

	cpy = NULL;
	if (s1 && s2)
		cpy = (char*)malloc(sizeof(*cpy) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s1 || !s2 || !cpy)
		return (NULL);
	cpy = ft_strcpy(cpy, s1);
	cpy = ft_strcat(cpy, s2);
	return (cpy);
}
