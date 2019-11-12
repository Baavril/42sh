/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 15:23:41 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libft.h"
#include "parser_utils_shvar.h"

static uint64_t	ft_atoi_63bits(const char *str) /* should have an atoi base that recognize the base used */
{
	struct s_uint63	nbr;
	int				i;
	unsigned short	add;

	i = 0;
	nbr.val = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		++i;
	while (str[i] > 47 && str[i] < 58)
	{
		add = str[i] ^ ((1 << 5) | (1 << 4));
		if (nbr.val > nbr.val * 10 + add)
			return (0);
		nbr.val = nbr.val * 10 + add;
		++i;
	}
	return (nbr.val);
}

uint64_t	get_index(char *str)
{
	while (*str && *str != '[')
		++str;
	if (*str != '[')
		  return (-1);
	else
	{
		*str = '\0';
		++str;
		return (ft_atoi_63bits(str));
	}
}

_Bool	contains_array_subscript(char *str)
{
	if (*str == '(')
	{
		while (*str)
		{
			++str;
			if (*str == ')')
				return (1);
		}
	}
	return (0);
}