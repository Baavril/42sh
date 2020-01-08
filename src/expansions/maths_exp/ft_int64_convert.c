/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int64_convert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:30:02 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/08 17:11:30 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "maths_interne.h"

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
		ft_printf("digit: %c indice: %zu in base: %s gives res: %lli\n", *nbr, i, base, res);
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
	ft_printf("is not number base: %s in base: %s\n", expr, base);
//		print_error("value too great for base");
		return (CONV_FAIL);
	}
	ft_printf("is number base: %s in base: %s\n", expr, base);
	*value = ft_atoi64_base(expr, base);
	ft_printf("value_ft_64_convert: %lli\n", *value);
	return (CONV_SUCCESS);
}
