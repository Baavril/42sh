/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:28:34 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/15 16:46:03 by yberramd         ###   ########.fr       */
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

	if (history(BACKWARD, NULL, &input) <= 0)
		return (0);
	if (history(FORWARD, NULL, &cmd) <= 0)
		return (0);
	if (history(SWAP, NULL, &input) <= 0)
		return (0);
	if (history(GET, NULL, &cmd) <= 0)
		return (0);
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

	nbr = ft_atoi_history(str_nbr);
	(void)nbr;
	return (1);
}

int				ft_execute(char **option)
{
	char	*cmd;

	if (option[0] == NULL)
	{
		if (history(LAST, NULL, &cmd) <= 0)
			return (0);
		return (fc_exec_cmd());
	}
	else
		return (fc_s_option(option[0]));
}
