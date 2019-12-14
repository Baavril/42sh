/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:39:33 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/17 19:11:57 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isin(const char c, const char *charset)
{
	while (*charset)
	{
		if (!(*charset - c))
			return (1);
		charset++;
	}
	return (0);
}
