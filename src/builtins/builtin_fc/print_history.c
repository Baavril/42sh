/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:05:14 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/26 16:11:45 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

extern int			g_arg;

void			ft_arg_r(int i, int max)
{
	char	*cmd;

	while (history(BACKWARD, NULL, &cmd) != 2 && cmd && (i - max) > 0)
	{
		i--;
		if (!(g_arg & ARG_N) && (i - max) > 0)
			ft_printf("%d", i);
		if ((i - max) > 0)
			ft_printf("\t%s\n", cmd);
	}
}

static void		ft_two_number(char **argv, int max)
{
	int nbr[2];

	nbr[0] = ft_atoi_history(argv[0]);
	nbr[1] = ft_atoi_history(argv[1]);
	if (nbr[0] < 0)
		nbr[0] = max + nbr[0];
	if (nbr[1] < 0)
		nbr[1] = max + nbr[1];
	if (nbr[1] == 0)
		ft_number(nbr[0], INT_MAX, max);
	else if (nbr[0] == 0)
	{
		g_arg = g_arg | ARG_R;
		ft_number(nbr[1], INT_MAX, max);
	}
	else if (nbr[0] - nbr[1] > 0)
	{
		g_arg = g_arg | ARG_R;
		ft_number(nbr[1], nbr[0], max);
	}
	else
		ft_number(nbr[0], nbr[1], max);
}

static void		ft_one_number(char *str_nbr, int max)
{
	int		nbr;

	nbr = ft_atoi_history(str_nbr);
	ft_number(nbr, INT_MAX, max);
}

static void		ft_no_number(int max)
{
	int		i;
	char	*cmd;

	i = 1;
	max -= 17;
	history(FIRST, NULL, &cmd);
	if (history(GET, NULL, &cmd) && (i - max) > 0 && !(g_arg & ARG_R)
			&& i != (max + 17))
	{
		if (!(g_arg & ARG_N))
			ft_printf("%d", i);
		ft_printf("\t%s\n", cmd);
	}
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
	{
		i++;
		if (!(g_arg & ARG_N) && (i - max) > 0 && !(g_arg & ARG_R)
				&& i != (max + 17))
			ft_printf("%d", i);
		if ((i - max) > 0 && !(g_arg & ARG_R) && i != (max + 17))
			ft_printf("\t%s\n", cmd);
	}
	if (g_arg & ARG_R)
		ft_arg_r(i, max);
}

int				ft_print_history(char **argv)
{
	int		max;
	char	*cmd;

	max = 1;
	history(FIRST, NULL, &cmd);
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		max++;
	if (argv[0] && argv[1])
		ft_two_number(argv, max);
	else if (argv[0])
	{
		if (ft_strisnbr(argv[0]))
			ft_one_number(argv[0], max);
		else
			ft_dprintf(2, "42sh: fc: %s: numeric argument required\n", argv[0]);
	}
	else
		ft_no_number(max);
	return (1);
}
