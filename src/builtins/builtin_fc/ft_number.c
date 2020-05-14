/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 18:25:19 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/14 19:22:39 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

extern int		g_arg;

static void		ft_arg_r2(int i, int max, int nbr, int nbr2)
{
	char	*cmd;

	while (history(BACKWARD, NULL, &cmd) != 2 && cmd)
	{
		i--;
		if (!(g_arg & ARG_N) && ((i - nbr) >= 0
					|| i == (max - 1)) && (i - nbr2) <= 0)
			ft_printf("%d", i);
		if (((i - nbr) >= 0 || (i == max - 1)) && (i - nbr2) <= 0)
			ft_printf("\t%s\n", cmd);
	}
}

static void		ft_number_p(int nbr, int nbr2, int max)
{
	int		i;
	char	*cmd;

	i = 1;
	if (!(g_arg & ARG_R) && i != max && history(GET, NULL, &cmd)
			&& ((i - nbr) >= 0 || (i == max - 1)) && (i - nbr2) <= 0)
	{
		if (!(g_arg & ARG_N))
			ft_printf("%d", i);
		ft_printf("\t%s\n", cmd);
	}
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
	{
		i++;
		if (i != max && !(g_arg & ARG_N) && ((i - nbr) >= 0 || i == (max - 1))
				&& !(g_arg & ARG_R) && (i - nbr2) <= 0)
			ft_printf("%d", i);
		if (i != max && ((i - nbr) >= 0 || (i == max - 1))
				&& !(g_arg & ARG_R) && (i - nbr2) <= 0)
			ft_printf("\t%s\n", cmd);
	}
	if (g_arg & ARG_R)
		ft_arg_r2(i, max, nbr, nbr2);
}

static void		ft_number_n(int nbr, int max)
{
	int		i;
	char	*cmd;

	i = 1;
	nbr -= 1;
	max += nbr;
	if (history(GET, NULL, &cmd) && (i - max) > 0
			&& !(g_arg & ARG_R) && i != (max - nbr))
	{
		if (!(g_arg & ARG_N))
			ft_printf("%d", i);
		ft_printf("\t%s\n", cmd);
	}
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
	{
		i++;
		if (!(g_arg & ARG_N) && (i - max) > 0 && !(g_arg & ARG_R)
				&& i != (max - nbr))
			ft_printf("%d", i);
		if ((i - max) > 0 && !(g_arg & ARG_R) && i != (max - nbr))
			ft_printf("\t%s\n", cmd);
	}
	if (g_arg & ARG_R)
		ft_arg_r(i, max);
}

void			ft_number(int nbr, int nbr2, int max)
{
	char	*cmd;

	if (nbr == 0)
		nbr = INT_MAX;
	history(FIRST, NULL, &cmd);
	if (nbr > 0)
		ft_number_p(nbr, nbr2, max);
	else if (nbr < 0)
		ft_number_n(nbr, max);
}
