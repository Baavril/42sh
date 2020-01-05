/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 23:50:21 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/09 20:29:22 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"

int			ft_find_inner_expr(char *expr, size_t *inner_par, size_t *end_par)
{
	size_t		i;
	size_t		flag;

	i = 0;
	flag = 0;
	*inner_par = 0;
	*end_par = 0;
	while (expr[i])
	{
		if (expr[i] == '(')
		{
			flag = 1;
			*inner_par = i;
		}
		else if (expr[i] == ')')
		{
			*end_par = i;
			return (flag);
		}
		i++;
	}
	return (0); // erreur de parentheses
}

int			ft_parentheses_nbr(char *expr)
{
	size_t		i;
	size_t		par_nbr;
	size_t		par_check;
	size_t		brk_check;

	i = 0;
	brk_check = 0;
	par_check = 0;
	par_nbr = 0;
	while (expr[i])
	{
		if (expr[i] == '(')
		{
			par_nbr++;
			par_check++;
		}
		if (expr[i] == ')')
			par_check--;
		if (expr[i] == '[')
			brk_check++;
		if (expr[i] == ']')
			brk_check--;
		i++;
	}
	return ((par_check) || (brk_check) ? -1 : par_nbr);
}
