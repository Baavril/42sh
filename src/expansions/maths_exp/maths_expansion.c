/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:48:38 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/08 16:16:34 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"
#include "expansions.h"

size_t		maths_len(char *token)
{
	size_t		i;
	int		opar;

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

	ft_putendl("entree d'extension");
	if ((par = ft_parentheses_nbr(to_expand)) < 0)
	{
//		print_error(PARENTHES_NBR || BRACKET_NBR);
		return (ERROR);
	}
	ft_putendl("fin de parenthese test");
	while (par > 0)
	{
		ft_putendl("\navant eval inter_parenthes");
		if (!(to_expand = ft_eval_inner_parentheses(to_expand)))
			return (ERROR);
		ft_putendl("apres eval inter_parenthes\n");
		par--;
	}
		ft_putendl("\nEvaluation de l'expression principale");
	if (ft_eval(to_expand, &res) == CONV_FAIL)
		return (ERROR);

	{
	ft_putendl("\nReussite de l'evaluation");
	ft_putstr("valeur en sortie: ");
	ft_printf("%lli\n", res);
	}

	*expansion = ft_itoa64(res);
	return (SUCCESS);
}

int			maths_exp(char **token)
{
	size_t	end;
	char	*to_expand;
	char	*expansion;

	expansion = NULL;
	end = maths_len(*token);
	to_expand = ft_strndup(*token + 3, end - 3);
	if (ft_maths_expansion(to_expand, &expansion) == ERROR)
	{
		free(to_expand);
		return (ERROR);
	}
	free(to_expand);
	ft_printf("%s\n", *token);
	free(*token);
	*token = expansion;
	return (SUCCESS);
}
