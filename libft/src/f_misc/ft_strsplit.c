/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 21:27:42 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/03 14:06:09 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_word(char const *str, const char *charset)
{
	size_t	k;

	k = ft_isin(*str, charset) ? 0 : 1;
	while (*str)
	{
		while (*str && !ft_isin(*str, charset))
			str++;
		while (*str && ft_isin(*str, charset))
			str++;
		if (*str)
			k++;
	}
	return (k);
}

char			**ft_strsplit(char const *str, const char *charset)
{
	size_t	k;
	size_t	l;
	char	**res;

	if (!(k = 0) && !*charset)
		return (NULL);
	if (!(res = (char**)malloc(sizeof(*res) * (ft_word(str, charset) + 1))))
		return (NULL);
	while (!(l = 0) && *str)
	{
		while (*str && ft_isin(*str, charset))
			str++;
		while (str[l] && !ft_isin(str[l], charset))
			l++;
		if (!(l))
			break ;
		res[k++] = ft_strndup(str, l);
		str += l;
	}
	res[k] = NULL;
	return (res);
}
