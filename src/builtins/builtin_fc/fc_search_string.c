/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_search_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:47:48 by yberramd          #+#    #+#             */
/*   Updated: 2020/06/01 19:56:51 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

extern int		g_arg;

static int	f_arg_non_nbr(char **argv, int max)
{
	(void)argv, (void)max;
	return (1);
}

static int	f_arg_nbr(char **argv, int max)
{
	int			nbr;
	static int	i = 0;
	char		*cmd;

	(void)cmd, (void)max;
	nbr = ft_atoi_history(argv[0]);
	if (nbr == 0)
		nbr = INT_MAX;
	if (nbr > 0)
	{
		ft_printf("%d\n", i);
	}
	else if (nbr < 0)
	{
	}
	return (1);
}

static int	fc_move_hist(char **argv, int max)
{
	if (!ft_strisnbr(argv[0]))
		return (f_arg_non_nbr(argv, max));
	else
		return (f_arg_nbr(argv, max));
}

void		fc_search_string(char **argv, int max)
{
	ft_printf("en attente [%s] max = [%d]\n", argv[0], max);
	fc_move_hist(argv, max);
}
