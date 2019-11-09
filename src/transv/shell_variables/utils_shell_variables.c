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

#include "libft.h"

int		get_index(char *str)
{
	while (*str && *str != '[')
		++str;
	if (*str != '[')
		  return (-1);
	else
	{
		*str = '\0';
		++str;
		return (ft_atoi(str)); /* should be a special atoi, maybe a ft_atoull63bits() */
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