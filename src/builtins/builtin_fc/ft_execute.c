/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:28:34 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/24 16:27:54 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

int				ft_atoi_history(const char *str)
{
	unsigned int	nbr;
	int				i;
	int				sign;
	unsigned short	val;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		++i;
	if (str[i] == '-')
	{
		sign = -1;
		++i;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		val = str[i] ^ ((1 << 5) | (1 << 4));
		if (nbr > (nbr * 10 + val))
			return (nbr * sign);
		nbr = nbr * 10 + val;
		++i;
	}
	return (nbr * sign);
}

static int		fc_exec_cmd(void)
{
	char *cmd;
	char *input;

	history(BACKWARD, NULL, &input);
	history(LAST, NULL, &cmd);
	if (history(SWAP, NULL, &input) <= 0)
		return (0);
	history(GET, NULL, &cmd);
	if (!(input = ft_strdup(cmd)))
		return (0);
	ft_printf("%s\n", input);
	execute(input);
	ft_strdel(&input);
	update_intern_vars();
	return (1);
}

static int		fc_s_option(char *str_nbr)
{
	int		nbr;
	char	*cmd;

	nbr = ft_atoi_history(str_nbr);
	while (nbr > 0)
	{
		history(FORWARD, NULL, &cmd);
		nbr--;
	}
	fc_exec_cmd();
	return (1);
}

int				ft_execute(char **option)
{
	char	*cmd;

	if (option[0] == NULL)
	{
		history(LAST, NULL, &cmd);
		return (fc_exec_cmd());
	}
	else
	{
		history(FIRST, NULL, &cmd);
		return (fc_s_option(option[0]));
	}
}
