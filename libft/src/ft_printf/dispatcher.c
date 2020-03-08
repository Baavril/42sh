/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:51:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/07 13:47:49 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

#include "struct_disp.h"
#include "specifiers.h"

static const t_specifier	g_specifier[] =
{
	{ 'c', (void*)&ft_chr},
	{ 'd', (void*)&ft_nbr},
	{ 'e', (void*)&ft_nbr},
	{ 'f', (void*)&ft_double},
	{ 'i', (void*)&ft_nbr},
	{ 'o', (void*)&ft_octal},
	{ 's', (void*)&ft_str},
	{ 'u', (void*)&ft_unbr},
	{ 'x', (void*)&ft_lhexa},
	{ 'X', (void*)&ft_uhexa},
	{ 'C', (void*)&ft_wchr},
	{ 'p', (void*)&ft_p},
	{ 'n', (void*)&ft_n},
	{ 'D', (void*)&ft_upnbr},
	{ 'O', (void*)&ft_upoc},
	{ 'U', (void*)&ft_upunbr},
	{ 'E', (void*)&ft_nbr},
	{ 'F', (void*)&ft_double},
	{ 'g', (void*)&ft_nbr},
	{ 'G', (void*)&ft_nbr},
	{ 'a', (void*)&ft_nbr},
	{ 'A', (void*)&ft_nbr},
	{ 'S', (void*)&ft_wstr},
	{ 'r', (void*)&ft_nbr},
	{ 'b', (void*)&ft_b},
	{ 'y', (void*)&ft_y}
};

void	*dispatcher(char c)
{
	int	i;

	i = 0;
	while (i < 26 && g_specifier[i].type ^ c)
		++i;
	if (i == 26)
		return (NULL);
	else
		return (g_specifier[i].f);
}
