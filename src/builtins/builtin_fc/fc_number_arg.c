/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_number_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:30:57 by tgouedar          #+#    #+#             */
/*   Updated: 2020/07/13 19:09:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

static int		str_exist(char **argv)
{
	char	*cmd;

	history(FIRST, NULL, &cmd);
	if (ft_strisnbr(argv[0]))
	{
		if (ft_strfchr(argv[1], cmd))
			return (0);
		while (history(FORWARD, NULL, &cmd) != 2)
			if (ft_strfchr(argv[1], cmd))
				return (0);
	}
	else
	{
		if (ft_strfchr(argv[0], cmd))
			return (0);
		while (history(FORWARD, NULL, &cmd) != 2)
			if (ft_strfchr(argv[0], cmd))
				return (0);
	}
	return (1);
}

static void			ft_plop_un(char **argv, t_fc *explorer, int max, int nbr)
{
	if (explorer->i == 0)
	{
		history(LAST, NULL, &(explorer->cmd));
		while ((explorer->found = ft_strfchr(argv[0], explorer->cmd)) == 0
		&& (max - explorer->i) > nbr)
		{
			history(BACKWARD, NULL, &(explorer->cmd));
			(explorer->i)++;
		}
		while (explorer->found == 0 && ft_strfchr(argv[0], explorer->cmd) == 0)
		{
			history(BACKWARD, NULL, &(explorer->cmd));
			explorer->i++;
		}
	}
	else if (explorer->found > 0 && (max - explorer->i) > nbr)
	{
		history(BACKWARD, NULL, &(explorer->cmd));
		(explorer->i)++;
	}
	else if (explorer->found == 0 && (max - explorer->i) < nbr)
	{
		history(FORWARD, NULL, &(explorer->cmd));
		(explorer->i)++;
	}
}

static void			ft_plop_zero(char **argv, t_fc *explorer, int max, int nbr)
{
	if (explorer->i == 0)
	{
		history(LAST, NULL, &(explorer->cmd));
		while ((explorer->found = ft_strfchr(argv[1], explorer->cmd)) == 0
		&& (max - explorer->i) > nbr)
		{
			history(BACKWARD, NULL, &(explorer->cmd));
			(explorer->i)++;
		}
		if (explorer->found == 1)
		{
			explorer->found = max - explorer->i;
			while ((max - explorer->i) > nbr
			&& history(BACKWARD, NULL, &(explorer->cmd)))
				(explorer->i)++;
		}
	}
	else if (explorer->found > 0 && (max - explorer->i) < explorer->found)
	{
		history(FORWARD, NULL, &(explorer->cmd));
		(explorer->i)--;
	}
	else if (explorer->found == 0)
	{
		if (ft_strfchr(argv[1], explorer->cmd) != 0)
			return ;
		history(BACKWARD, NULL, &(explorer->cmd));
		(explorer->i)++;
	}
}

static int			ft_set_arg_nbr(char **argv, int max)
{
	int		nbr;

	if (ft_strisnbr(argv[0]))
		nbr = ft_atoi_history(argv[0]);
	else
		nbr = ft_atoi_history(argv[1]);
	if (nbr == 0)
		nbr = INT_MAX;
	if (nbr < 0)
		if ((nbr = max + nbr) < 0)
			nbr = 1;
	return (nbr);
}

int				f_arg_nbr(char **argv, int max, int reset)
{
	int				nbr;
	static t_fc		explorer = {0, 0, NULL};

	if (reset)
		return (reset_arg(&explorer));
	if (explorer.i == 0 && str_exist(argv))
		return (-2);
	if ((!ft_strisnbr(argv[0]) && !ft_strisnbr(argv[0]))
	|| (nbr = ft_set_arg_nbr(argv, max)) <= 0)
		return (-1);
	if (ft_strisnbr(argv[0]))
		ft_plop_zero(argv, &explorer, max, nbr);
	else
		ft_plop_un(argv, &explorer, max, nbr);
	return (max - explorer.i);
}
