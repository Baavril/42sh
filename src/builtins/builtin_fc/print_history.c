/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:05:14 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/12 15:31:03 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

static void		ft_number(int arg, int nbr, int nbr2, int max)
{
	int		i;
	char	*cmd;

	i = 1;
	(void)nbr2;
	if (nbr == 0)
		nbr = INT_MAX;
	if (nbr > 0)
	{
		history(FIRST, NULL, &cmd);
		if (!(arg & ARG_R) && i != max && history(GET, NULL, &cmd)
				&& ((i - nbr) >= 0 || (i == max - 1)) && (i - nbr2) <= 0)
		{
			if (!(arg & ARG_N))
				ft_printf("%d", i);
			ft_printf("\t%s\n", cmd);
		}
		while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		{
			i++;
			if (i != max && !(arg & ARG_N) && ((i - nbr) >= 0 || i == (max - 1))
					&& !(arg & ARG_R) && (i - nbr2) <= 0)
				ft_printf("%d", i);
			if (i != max && ((i - nbr) >= 0 || (i == max - 1))
					&& !(arg & ARG_R) && (i - nbr2) <= 0)
				ft_printf("\t%s\n", cmd);
		}
		if (arg & ARG_R)// SI ARG R EST UTILISER
		{
			while (history(BACKWARD, NULL, &cmd) != 2 && cmd)
			{
				i--;
				if (!(arg & ARG_N) && ((i - nbr) >= 0
							|| i == (max - 1)) && (i - nbr2) <= 0)
					ft_printf("%d", i);
				if (((i - nbr) >= 0 || (i == max - 1)) && (i - nbr2) <= 0)
					ft_printf("\t%s\n", cmd);
			}
		}
	}
	else if (nbr < 0)
	{
		nbr -= 1;
		max += nbr;
		history(FIRST, NULL, &cmd);
		if (history(GET, NULL, &cmd) && (i - max) > 0 && !(arg & ARG_R) && i != (max - nbr))
		{
			if (!(arg & ARG_N))
				ft_printf("%d", i);
			ft_printf("\t%s\n", cmd);
		}
		while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		{
			i++;
			if (!(arg & ARG_N) && (i - max) > 0 && !(arg & ARG_R) && i != (max - nbr))
				ft_printf("%d", i);
			if ((i - max) > 0 && !(arg & ARG_R) && i != (max - nbr))
				ft_printf("\t%s\n", cmd);
		}
		if (arg & ARG_R)
		{
			while (history(BACKWARD, NULL, &cmd) != 2 && cmd && (i - max) > 0)
			{
				i--;
				if (!(arg & ARG_N) && (i - max) > 0)
					ft_printf("%d", i);
				if ((i - max) > 0)
					ft_printf("\t%s\n", cmd);
			}
		}
	}
}

static void		ft_two_number(int arg, char **argv, int max)
{
	int nbr[2];

	nbr[0] = ft_atoi_history(argv[0]);
	nbr[1] = ft_atoi_history(argv[1]);
	if (nbr[0] < 0)
		nbr[0] = max + nbr[0];
	if (nbr[1] < 0)
		nbr[1] = max + nbr[1];
	if (nbr[1] == 0)
		ft_number(arg, nbr[0], INT_MAX, max);
	else if (nbr[0] == 0)
	{
		arg = arg | ARG_R;
		ft_number(arg, nbr[1], INT_MAX, max);
	}
	else if (nbr[0] - nbr[1] > 0)
	{
		arg = arg | ARG_R;
		ft_number(arg, nbr[1], nbr[0], max);
	}
	else
		ft_number(arg, nbr[0], nbr[1], max);
}

static void		ft_one_number(int arg, char *str_nbr, int max)
{
	int		nbr;

	nbr = ft_atoi_history(str_nbr);
	ft_number(arg, nbr, INT_MAX, max);
}

static void		ft_no_number(int arg, int max)
{
	int		i;
	char	*cmd;

	i = 1;
	max -= 17;
	history(FIRST, NULL, &cmd);
	if (history(GET, NULL, &cmd) && (i - max) > 0 && !(arg & ARG_R)
			&& i != (max + 17))
	{
		if (!(arg & ARG_N))
			ft_printf("%d", i);
		ft_printf("\t%s\n", cmd);
	}
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
	{
		i++;
		if (!(arg & ARG_N) && (i - max) > 0 && !(arg & ARG_R)
				&& i != (max + 17))
			ft_printf("%d", i);
		if ((i - max) > 0 && !(arg & ARG_R) && i != (max + 17))
			ft_printf("\t%s\n", cmd);
	}
	if (arg & ARG_R)
	{
		while (history(BACKWARD, NULL, &cmd) != 2 && cmd && (i - max) > 0)
		{
			i--;
			if (!(arg & ARG_N) && (i - max) > 0)
				ft_printf("%d", i);
			if ((i - max) > 0)
				ft_printf("\t%s\n", cmd);
		}
	}
}

int		ft_print_history(int arg, char **argv)
{
	int		max;
	char	*cmd;

	max = 1;
	history(FIRST, NULL, &cmd);
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		max++;
	if (argv[0] && argv[1])
	{
		ft_two_number(arg, argv, max);
		ft_strdel(&argv[0]);
		argv[0] = NULL;
		ft_strdel(&argv[1]);
		argv[1] = NULL;
	}
	else if (argv[0])
	{
		if (ft_strisnbr(argv[0]))
			ft_one_number(arg, argv[0], max);
		else
			ft_dprintf(2, "42sh: fc: %s: numeric argument required\n", argv[0]);
		ft_strdel(&argv[0]);
		argv[0] = NULL;
	}
	else
		ft_no_number(arg, max);
	return (1);
}
