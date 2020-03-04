/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int64_convert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:30:02 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/15 15:40:54 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "maths_expansion.h"
#include "error.h"

extern char		*g_exptok;

static int64_t	ft_atoi64_base(char *nbr, const char *base)
{
	int64_t		base_len;
	int64_t		res;
	size_t		i;

	res = 0;
	base_len = ft_strlen(base);
	while (*nbr)
	{
		i = ft_indice(*nbr, base);
		res = res * base_len + i;
		nbr++;
	}
	return (res);
}

static char		*ft_get_base(char **expr)
{
	if (**expr == '0')
	{
		(*expr)++;
		if (**expr == 'x' || **expr == 'X')
		{
			(*expr)++;
			ft_strlower(*expr);
			return (HEX_BASE);
		}
		return (OCT_BASE);
	}
	return (DEF_BASE);
}

int				ft_int64_convert(int64_t *value, char *expr, char *base)
{
	if (!(base))
		base = ft_get_base(&expr);
	if (!(ft_isnumber_base(expr, base)))
	{
		psherror(e_base_error, g_exptok, e_maths_type);
		return (CONV_FAIL);
	}
	*value = ft_atoi64_base(expr, base);
	return (CONV_SUCCESS);
}
