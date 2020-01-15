/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:48:38 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/15 15:41:16 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"
#include "expansions.h"

char		*g_exptok = NULL;

size_t		maths_len(char *token)
{
	size_t		i;
	int			opar;

	i = 3;
	opar = 0;
	while (token[i])
	{
		if (token[i] == '(')
			opar++;
		if ((token[i] == ')' && token[i + 1] == ')') && !opar)
			return (i);
		if (token[i] == ')')
			opar--;
		++i;
	}
	return (i);
}

int			ft_maths_expansion(char *to_expand, char **expansion)
{
	int				par;
	int64_t			res;

	if ((par = ft_parentheses_nbr(to_expand)) < 0)
		return (ERROR);
	while (par > 0)
	{
		if (!(to_expand = ft_eval_inner_parentheses(to_expand)))
			return (ERROR);
		par--;
	}
	if (ft_eval(to_expand, &res) == CONV_FAIL)
		return (ERROR);
	*expansion = ft_itoa64(res);
	return (SUCCESS);
}

int			maths_exp(char **token)
{
	size_t	end;
	char	*expansion;

	expansion = NULL;
	end = maths_len(*token);
	g_exptok = ft_strndup(*token + 3, end - 3);
	if (ft_maths_expansion(g_exptok, &expansion) == ERROR)
	{
		ft_strdel(&g_exptok);
		return (ERROR);
	}
	ft_strdel(&g_exptok);
	free(*token);
	*token = expansion;
	return (SUCCESS);
}
