/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:52:02 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/17 19:25:36 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t	i;

	i = 0;
	while (s[i] && !(ft_isin(s[i], charset)))
		i++;
	return (i);
}
