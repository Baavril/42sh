/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:27:52 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/17 20:04:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_tablen(char **table)
{
	size_t	nb;

	nb = 0;
	while (table[nb])
	{
		++nb;
	}
	return (nb);
}
