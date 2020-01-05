/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:48:38 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/03 17:21:27 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"
#include "maths_module.h"

int			ft_maths_expansion(char *to_expand, char **expansion)
{
	int				par;
	int64_t			res;

	ft_putendl("entree d'extension");
	if ((par = ft_parentheses_nbr(to_expand)) < 0)
	{
//		print_error(PARENTHES_NBR || BRACKET_NBR);
		return (MATHS_ERROR);
	}
	ft_putendl("fin de parenthese test");
	while (par > 0)
	{
		ft_putendl("\navant eval inter_parenthes");
		if (!(to_expand = ft_eval_inner_parentheses(to_expand)))
			return (MATHS_ERROR);
		ft_putendl("apres eval inter_parenthes\n");
		par--;
	}
		ft_putendl("\nEvalution de l'exepresion principale");
	if (ft_eval(to_expand, &res) == CONV_FAIL)
		return (MATHS_ERROR);

	{
	ft_putendl("\nReussite de l'evaluation");
	ft_putstr("valeur en sortie: ");
	ft_printf("%lli\n", res);
	}

	*expansion = ft_itoa64(res);
	return (MATHS_SUCCESS);
}
