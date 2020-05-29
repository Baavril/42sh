/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_write_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:16:48 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/29 16:47:21 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

extern int		g_arg;

static void		ft_number_p(int nbr, int nbr2, int max, int fd)
{
	int		i;
	char	*cmd;

	i = 1;
	if (!(g_arg & ARG_R) && i != max && history(GET, NULL, &cmd)
			&& ((i - nbr) >= 0 || (i == max - 1)) && (i - nbr2) <= 0)
		ft_dprintf(fd, "%s\n", cmd);
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
	{
		i++;
		if (i != max && ((i - nbr) >= 0 || (i == max - 1))
				&& !(g_arg & ARG_R) && (i - nbr2) <= 0)
			ft_dprintf(fd, "%s\n", cmd);
	}
	if (g_arg & ARG_R)
		while (history(BACKWARD, NULL, &cmd) != 2 && cmd)
		{
			i--;
			if (((i - nbr) >= 0 || (i == max - 1)) && (i - nbr2) <= 0)
				ft_dprintf(fd, "%s\n", cmd);
		}
}

static void		ft_number_n(int nbr, int max, int fd)
{
	int		i;
	char	*cmd;

	i = 1;
	nbr -= 1;
	max += nbr;
	if (history(GET, NULL, &cmd) && (i - max) > 0
			&& !(g_arg & ARG_R) && i != (max - nbr))
		ft_dprintf(fd, "%s\n", cmd);
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
	{
		i++;
		if ((i - max) > 0 && !(g_arg & ARG_R) && i != (max - nbr))
			ft_dprintf(fd, "%s\n", cmd);
	}
	if (g_arg & ARG_R)
		while (history(BACKWARD, NULL, &cmd) != 2 && cmd && (i - max) > 0)
		{
			i--;
			if ((i - max) > 0)
				ft_dprintf(fd, "%s\n", cmd);
		}
}

static void		ft_number_w(int nbr, int nbr2, int max, int fd)
{
	char	*cmd;

	if (nbr == 0)
		nbr = INT_MAX;
	history(FIRST, NULL, &cmd);
	if (nbr > 0)
		ft_number_p(nbr, nbr2, max, fd);
	else if (nbr < 0)
		ft_number_n(nbr, max, fd);
}

void			ft_two_number_w(char **argv, int max, int fd)
{
	int nbr[2];

	nbr[0] = ft_atoi_history(argv[0]);
	nbr[1] = ft_atoi_history(argv[1]);
	if (nbr[0] < 0)
		nbr[0] = max + nbr[0];
	if (nbr[1] < 0)
		nbr[1] = max + nbr[1];
	if (nbr[1] == 0)
		ft_number_w(nbr[0], INT_MAX, max, fd);
	else if (nbr[0] == 0)
	{
		g_arg = g_arg | ARG_R;
		ft_number_w(nbr[1], INT_MAX, max, fd);
	}
	else if (nbr[0] - nbr[1] > 0)
	{
		g_arg = g_arg | ARG_R;
		ft_number_w(nbr[1], nbr[0], max, fd);
	}
	else
		ft_number_w(nbr[0], nbr[1], max, fd);
}

void			ft_one_number_w(char *str_nbr, int max, int fd)
{
	int		nbr;

	nbr = ft_atoi_history(str_nbr);
	ft_number_w(nbr, INT_MAX, max, fd);
}
