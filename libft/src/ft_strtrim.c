/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:04:41 by abarthel          #+#    #+#             */
/*   Updated: 2019/01/29 14:16:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!s)
		return (NULL);
	while (*s == '\t' || *s == ' ' || *s == '\n')
		++s;
	while (s[i])
		++i;
	if (i)
		--i;
	while (s[i] == '\t' || s[i] == ' ' || s[i] == '\n')
		--i;
	cpy = ft_strsub(s, 0, i + 1);
	return (cpy);
}
