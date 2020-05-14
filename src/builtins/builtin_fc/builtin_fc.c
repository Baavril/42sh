/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:34:42 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/14 21:09:25 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

extern int	g_retval;
int			g_arg;

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

/*
** boucle infini sur fc -s // ajout du seaarch sur fc
*/

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

static int		ft_execute(char **option)
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

static int		ft_strdel_option(char ***option)
{
	if (option && *option)
	{
		if ((*option)[0])
			free(*option[0]);
		if ((*option)[1])
			free(*option[1]);
		free(*option);
		option = NULL;
	}
	return (0);
}

static int		ft_fc(void)
{
	ft_printf("fc loloolololoololol\n");
	return (1);
}

/*
** message d'erreur si l'historique est vide (A AJOUTER)
*/

int				ft_strisnbr(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		opt_arg(int opt)
{
	if (opt == 108)
		g_arg = g_arg | ARG_L;
	else if (opt == 115)
		g_arg = g_arg | ARG_S;
	else if (opt == 110)
		g_arg = g_arg | ARG_N;
	else if (opt == 114)
		g_arg = g_arg | ARG_R;
	else if (opt == 101)
		g_arg = g_arg | ARG_E;
	return (1);
}

static int		ft_bazar(char ***option, int sh)
{
	int	ret;

	if (sh == 1)
	{
		if (!((*option) = (char**)malloc(sizeof(char*) * 2)))
		{
			ft_dprintf(2, "cannot allocate memory\n");
			return (0);
		}
		(*option)[0] = NULL;
		(*option)[1] = NULL;
		return (1);
	}
	else
	{
		if (g_arg & ARG_S)
			ret = ft_execute(*option);
		else if (g_arg & ARG_L)
			ret = ft_print_history(*option);
		else
			ret = ft_fc();
		ft_strdel_option(option);
		return (ret);
	}
}

int				cmd_fc(int argc, char **argv)
{
	char	**option;
	int		ret;
	int		opt;

	g_arg = 0;
	if (!ft_bazar(&option, 1))
		return (0);
	while ((opt = ft_parser(argc, argv, "rnl::s:e::", option)) != -1)
	{
		if (opt == 63)
		{
			ft_dprintf(2, "fc: usage: fc [-e ename] [-lnr] [first] [last]");
			ft_dprintf(2, " or fc -s [pat=rep] [command]\n");
		}
		else if (opt == 0)
			ft_dprintf(2, "cannot allocate memory\n");
		else
			opt_arg(opt);
		if (opt == 63 || opt == 0)
			return (ft_strdel_option(&option));
	}
	ret = ft_bazar(&option, 2);
	return (ret);
}
