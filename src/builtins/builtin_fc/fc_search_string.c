/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_search_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:47:48 by yberramd          #+#    #+#             */
/*   Updated: 2020/06/07 20:37:28 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"
#include "error.h"

extern int		g_arg;

static int	reset_arg(int *i, int *found, char **cmd)
{
	*i = 0;
	*found = 0;
	*cmd = NULL;
	return (1);
}

static int	f_arg_non_nbr(char **argv, int max, int reset)
{
	int	i;
	int	found;
	char	*cmd;

	(void)argv, (void)max, (void)reset;
	if (reset)
		return (reset_arg(&i, &found, &cmd));
	if (argv[1])
	{
	}
	else
	{
	}
	return (1);
}

static int	str_exist(char **argv)
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

static int	f_arg_nbr(char **argv, int max, int reset)
{
	int			nbr;
	static int	found = 0;
	static int	i = 0;
	static char	*cmd = NULL;

	if (reset)
		return (reset_arg(&i, &found, &cmd));
	if (i == 0 && str_exist(argv))
		return (-2);
	if (ft_strisnbr(argv[0]))
		nbr = ft_atoi_history(argv[0]);
	else
		nbr = ft_atoi_history(argv[1]);
	if (nbr == 0)
		nbr = INT_MAX;
	if (nbr < 0)
		if ((nbr = max + nbr) < 0)
			nbr = 1;
	if (nbr > 0 && ft_strisnbr(argv[0]))
	{
		if (i == 0)
		{
			history(LAST, NULL, &cmd);
			while ((found = ft_strfchr(argv[1], cmd)) == 0 && (max - i) > nbr)
			{
				history(BACKWARD, NULL, &cmd);
				i++;
			}
			if (found == 1)
			{
				found = max - i;
				while ((max - i) > nbr && history(BACKWARD, NULL, &cmd))
					i++;
			}
		}
		else if (found > 0 && (max - i) < found)
		{
			history(FORWARD, NULL, &cmd);
			i--;
		}
		else if (found == 0)
		{
			if (ft_strfchr(argv[1], cmd) != 0)
				return (max - i);
			history(BACKWARD, NULL, &cmd);
			i++;
		}
		return (max - i);
	}
	else if (nbr > 0 && ft_strisnbr(argv[1]))
	{
		if (i == 0)
		{
			history(LAST, NULL, &cmd);
			while ((found = ft_strfchr(argv[0], cmd)) == 0 && (max - i) > nbr)
			{
				history(BACKWARD, NULL, &cmd);
				i++;
			}
			while (found == 0 && ft_strfchr(argv[0], cmd) == 0)
			{
				history(BACKWARD, NULL, &cmd);
				i++;
			}
		}
		else if (found > 0 && (max - i) > nbr)
		{
			history(BACKWARD, NULL, &cmd);
			i++;
		}
		else if (found == 0 && (max - i) < nbr)
		{
			history(FORWARD, NULL, &cmd);
			i++;
		}
		return (max - i);
	}
	return (-1);
}

static int	fc_move_hist(char **argv, int max, int reset)
{
	if (!ft_strisnbr(argv[0]) && !(argv[1] && ft_strisnbr(argv[1])))
		return (f_arg_non_nbr(argv, max, reset));
	else
		return (f_arg_nbr(argv, max, reset));
}

void		fc_search_string(char **argv, int max)
{
	char	*cmd;
	int		ret;
	int		tmp;

	tmp = 0;
	while ((ret = fc_move_hist(argv, max, 0)) > 0 && tmp != ret)
	{
		tmp = ret;
		ft_printf("%d\t", tmp);
		history(GET, NULL, &cmd);
		ft_printf("%s\n", cmd);
	}
	ft_printf("ret =%d\n", ret);
	if (ret == -2)
		psherror(e_history_specification_out_of_range, NULL, e_invalid_type);
	fc_move_hist(argv, max, 1);
}
