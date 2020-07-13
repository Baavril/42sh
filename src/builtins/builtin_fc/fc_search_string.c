/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_search_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:47:48 by yberramd          #+#    #+#             */
/*   Updated: 2020/07/13 18:52:30 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"
#include "error.h"

extern int		g_arg;

int				reset_arg(t_fc *explorer)
{
	explorer->i = 0;
	explorer->found = 0;
	explorer->cmd = NULL;
	return (1);
}

static int		f_arg_non_nbr(char **argv, int max, int reset)
{
	(void)argv;
	(void)max;
	(void)reset;
	if (reset)
		return (1);
	if (argv[1])
	{
	}
	else
	{
	}
	return (1);
}

static int		fc_move_hist(char **argv, int max, int reset)
{
	if (!ft_strisnbr(argv[0]) && !(argv[1] && ft_strisnbr(argv[1])))
		return (f_arg_non_nbr(argv, max, reset));
	else
		return (f_arg_nbr(argv, max, reset));
}

void			fc_search_string(char **argv, int max)
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
