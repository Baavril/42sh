/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:41:38 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/15 15:38:06 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_variables.h"
#include "maths_interne.h"
#include "expansions.h"
#include "error.h"
#include "libft.h"

extern char		*g_exptok;

int				ft_isnumber(char *to_test)
{
	size_t	i;

	i = 0;
	while (to_test[i])
	{
		if (!(ft_isdigit(to_test[i])))
			return (0);
		i++;
	}
	return (1);
}

static int		ft_arg_value_base(char *base, char *nbr, int64_t *value)
{
	char	conv_base[65];
	size_t	base_len;

	*nbr = '\0';
	nbr++;
	base_len = 0;
	if ((ft_strchr(nbr, '#')))
	{
		psherror(e_invalid_number, g_exptok, e_maths_type);
		return (CONV_FAIL);
	}
	if (ft_isnumber(base))
		base_len = ft_atoi(base);
	if (base_len < 2 || base_len > 64)
	{
		psherror(e_invalid_base, g_exptok, e_maths_type);
		return (CONV_FAIL);
	}
	ft_memcpy(conv_base, BASE, base_len);
	conv_base[base_len] = '\0';
	if (base_len < 37)
		ft_strlower(nbr);
	return (ft_int64_convert(value, nbr, conv_base));
}

int				ft_arg_value(char *token, int64_t *value)
{
	char	*expr;

	*value = 0;
	if ((expr = ft_strchr(token, '#')))
		return (ft_arg_value_base(token, expr, value));
	if (ft_isdigit(*token))
		return (ft_int64_convert(value, token, NULL));
	expr = getshvar(token);
	if (ft_isnumber(expr))
		return (ft_int64_convert(value, expr, DEF_BASE));
	if (ft_maths_expansion(expr, &expr) == SUCCESS)
		return (ft_int64_convert(value, expr, NULL));
	*value = 0;
	return (CONV_FAIL);
}
