/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_search_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:47:48 by yberramd          #+#    #+#             */
/*   Updated: 2020/06/02 18:27:05 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"
#include "error.h"

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
		if (i == 0)
		{
			history(FIRST, NULL, &cmd);
			while (i++ < nbr || ft_strcmp(argv[1], cmd) != 0)
				if (history(FORWARD, NULL, &cmd) == 2)
					return (-2);
		}
		if (ft_strcmp(argv[1], cmd) != 0 || i++ < nbr)
			if (history(FORWARD, NULL, &cmd) == 2)
				return (-2);
		return (i);
	}
	else if (nbr < 0)
	{
		if (i != 0)
			history(LAST, NULL, &cmd);
		ft_printf("%d\n", i);
	}
	return (-1);
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
	char	*cmd;
	int		ret;

	ft_printf("en attente [%s] max = [%d]\n", argv[0], max);
	while ((ret = fc_move_hist(argv, max)) != max && ret >= 0)
	{
		history(GET, NULL, &cmd);
		ft_printf("%s\n", cmd);
	}
	if (ret == -2)
		psherror(e_history_specification_out_of_range, NULL, e_invalid_type);
}
