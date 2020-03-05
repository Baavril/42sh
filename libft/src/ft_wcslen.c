/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcslen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:47:47 by abarthel          #+#    #+#             */
/*   Updated: 2019/03/05 12:06:05 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_wcslen(const wchar_t *ws)
{
	size_t	len;

	len = 0;
	while (ws[len])
		++len;
	return (len);
}
