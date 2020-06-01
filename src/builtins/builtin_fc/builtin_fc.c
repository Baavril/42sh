/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:34:42 by yberramd          #+#    #+#             */
/*   Updated: 2020/06/01 17:12:49 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

int			g_arg;

/*
** boucle infini sur fc -s // ajout du seaarch sur fc
*/

static int		ft_strdel_option(char ***option)
{
	if (option && *option)
	{
		if ((*option)[0])
			free((*option)[0]);
		if ((*option)[1])
			free((*option)[1]);
		free(*option);
		option = NULL;
	}
	return (0);
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

static int		ft_bazar(char ***option, int sh, char **argv)
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
			ret = ft_execute(*option);//attention si opt=string
		else if (g_arg & ARG_L)
			ret = ft_print_history(*option);
		else
			ret = ft_fc(*option, argv);//attention si opt=string
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
	if (!ft_bazar(&option, 1, argv))
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
	ret = ft_bazar(&option, 2, argv);
	return (ret);
}
