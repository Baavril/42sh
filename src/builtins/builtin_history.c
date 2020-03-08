/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:34:30 by yberramd          #+#    #+#             */
/*   Updated: 2020/03/08 10:51:45 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "libft.h"

char			*g_progname;

static int		ft_atoi_history(const char *str)
{
	int				i;
	unsigned long	nbr;
	unsigned short	val;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		++i;
	while (str[i] > 47 && str[i] < 58)
	{
		val = str[i] ^ ((1 << 5) | (1 << 4));
		nbr = nbr * 10 + val;
		if (nbr > 500)
			return (501);
		++i;
	}
	return (nbr);
}

static char		*twoarg_history(char **argv)
{
	int		i;
	int		max;
	int		nbr;
	char	*cmd;

	i = 1;
	max = 1;
	nbr = ft_atoi_history(argv[1]);
	history(FIRST, NULL, &cmd);
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		max++;
	max -= nbr;
	history(FIRST, NULL, &cmd);
	if (history(GET, NULL, &cmd) && (i - max) > 0)
		ft_printf("\t%d\t%s\n", i, cmd);
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
	{
		i++;
		if ((i - max) > 0)
			ft_printf("\t%d\t%s\n", i, cmd);
	}
	return (cmd);
}

static int		history_nbr(int argc, char **argv)
{
	int		i;
	char	*cmd;

	i = 1;
	if (argc == 2)
		cmd = twoarg_history(argv);
	else
	{
		history(FIRST, NULL, &cmd);
		if (history(GET, NULL, &cmd))
			ft_printf("\t%d\t%s\n", i, cmd);
		while (history(FORWARD, NULL, &cmd) != 2 && cmd)
			ft_printf("\t%d\t%s\n", ++i, cmd);
	}
	return ((cmd) ? 1 : 0);
}

int				cmd_history(int argc, char **argv)
{
	if (argc == 1 || (ft_isdigit(argv[1][0]) && argc == 2))
		return (history_nbr(argc, argv));
	else if (argc >= 2 && ft_isdigit(argv[1][0]))
		ft_dprintf(STDERR_FILENO, \
				"%s: history: too many arguments\n", g_progname);
	else if (argc >= 2 && argv[1][0] != '-')
		ft_dprintf(STDERR_FILENO,\
				"%s: history: %s: numeric argument required\n", \
				g_progname, argv[1]);
	return (0);
}
