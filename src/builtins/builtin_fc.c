/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:34:42 by yberramd          #+#    #+#             */
/*   Updated: 2020/03/03 19:02:09 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <getopt.h>

#include "history.h"
#include "libft.h"
#include "ft_getopt.h"
#include "history.h"
#include "parser.h"

#ifndef INT_MAX
# define INT_MAX 2147483647
#endif

static int		ft_atoi_history(const char *str)
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

static int		fc_s_no_option(void)
{
	char *cmd;
	char *input;

	history(LAST, NULL, &cmd);
	history(BACKWARD, NULL, &input);
	history(FORWARD, NULL, &cmd);
	history(SWAP, NULL, &input);
	history(GET, NULL, &cmd);
	if (!(input = ft_strdup(cmd)))
		return (0);
	ft_printf("%s\n", input);
	execute(input);
	ft_strdel(&input);
	update_intern_vars();
	return (1);
}

//probleme de compilation et de logique avec la fonction suivante
// le passage commenté est la fonction originale, la ligne rajoutée est pour 
//compiler a la zeub

static int		fc_s_option(char *str_nbr)
{
//	int		nbr;

//	nbr = ft_atoi_history(str_nbr);
	ft_atoi_history(str_nbr);
	return (1);
}

static int		ft_execute(char **option)
{
	if (option[0] == NULL)
		return (fc_s_no_option());
	else
		return (fc_s_option(option[0]));
}

static void		ft_strdel_option(char ***option)
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
}

static int		ft_fc(void)
{
	ft_printf("fc loloolololoololol\n");
	return (1);
}

/*
** message d'erreur si l'historique est vide (A AJOUTER)
*/

static void		ft_no_number(int arg, int max)
{
	int		i;
	char	*cmd;

	i = 1;
	max -= 17;
	history(FIRST, NULL, &cmd);
	if (history(GET, NULL, &cmd) && (i - max) > 0 && !(arg & ARG_R)
			&& i != (max + 17))
	{
		if (!(arg & ARG_N))
			ft_printf("%d", i);
		ft_printf("\t%s\n", cmd);
	}
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
	{
		i++;
		if (!(arg & ARG_N) && (i - max) > 0 && !(arg & ARG_R)
				&& i != (max + 17))
			ft_printf("%d", i);
		if ((i - max) > 0 && !(arg & ARG_R) && i != (max + 17))
			ft_printf("\t%s\n", cmd);
	}
	if (arg & ARG_R)
	{
		while (history(BACKWARD, NULL, &cmd) != 2 && cmd && (i - max) > 0)
		{
			i--;
			if (!(arg & ARG_N) && (i - max) > 0)
				ft_printf("%d", i);
			if ((i - max) > 0)
				ft_printf("\t%s\n", cmd);
		}
	}
}

static void		ft_number(int arg, int nbr, int nbr2, int max)
{
	int		i;
	char	*cmd;

	i = 1;
	(void)nbr2;
	if (nbr == 0)
		nbr = INT_MAX;
	if (nbr > 0)
	{
		history(FIRST, NULL, &cmd);
		if (!(arg & ARG_R) && i != max && history(GET, NULL, &cmd)
				&& ((i - nbr) >= 0 || (i == max - 1)) && (i - nbr2) <= 0)
		{
			if (!(arg & ARG_N))
				ft_printf("%d", i);
			ft_printf("\t%s\n", cmd);
		}
		while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		{
			i++;
			if (i != max && !(arg & ARG_N) && ((i - nbr) >= 0 || i == (max - 1))
					&& !(arg & ARG_R) && (i - nbr2) <= 0)
				ft_printf("%d", i);
			if (i != max && ((i - nbr) >= 0 || (i == max - 1))
					&& !(arg & ARG_R) && (i - nbr2) <= 0)
				ft_printf("\t%s\n", cmd);
		}
		if (arg & ARG_R)// SI ARG R EST UTILISER
		{
			while (history(BACKWARD, NULL, &cmd) != 2 && cmd)
			{
				i--;
				if (!(arg & ARG_N) && ((i - nbr) >= 0
							|| i == (max - 1)) && (i - nbr2) <= 0)
					ft_printf("%d", i);
				if (((i - nbr) >= 0 || (i == max - 1)) && (i - nbr2) <= 0)
					ft_printf("\t%s\n", cmd);
			}
		}
	}
	else if (nbr < 0)
	{
		nbr -= 1;
		max += nbr;
		history(FIRST, NULL, &cmd);
		if (history(GET, NULL, &cmd) && (i - max) > 0 && !(arg & ARG_R) && i != (max - nbr))
		{
			if (!(arg & ARG_N))
				ft_printf("%d", i);
			ft_printf("\t%s\n", cmd);
		}
		while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		{
			i++;
			if (!(arg & ARG_N) && (i - max) > 0 && !(arg & ARG_R) && i != (max - nbr))
				ft_printf("%d", i);
			if ((i - max) > 0 && !(arg & ARG_R) && i != (max - nbr))
				ft_printf("\t%s\n", cmd);
		}
		if (arg & ARG_R)
		{
			while (history(BACKWARD, NULL, &cmd) != 2 && cmd && (i - max) > 0)
			{
				i--;
				if (!(arg & ARG_N) && (i - max) > 0)
					ft_printf("%d", i);
				if ((i - max) > 0)
					ft_printf("\t%s\n", cmd);
			}
		}
	}
}

static void		ft_one_number(int arg, char *str_nbr, int max)
{
	int		nbr;

	nbr = ft_atoi_history(str_nbr);
	ft_number(arg, nbr, INT_MAX, max);
}

static void		ft_two_number(int arg, char **argv, int max)
{
	int nbr[2];

	nbr[0] = ft_atoi_history(argv[0]);
	nbr[1] = ft_atoi_history(argv[1]);
	if (nbr[0] < 0)
		nbr[0] = max + nbr[0];
	if (nbr[1] < 0)
		nbr[1] = max + nbr[1];
	if (nbr[1] == 0)
		ft_number(arg, nbr[0], INT_MAX, max);
	else if (nbr[0] == 0)
	{
		arg = arg | ARG_R;
		ft_number(arg, nbr[1], INT_MAX, max);
	}
	else if (nbr[0] - nbr[1] > 0)
	{
		arg = arg | ARG_R;
		ft_number(arg, nbr[1], nbr[0], max);
	}
	else
		ft_number(arg, nbr[0], nbr[1], max);
}

static int ft_strisnbr(char *str)
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

static int		ft_print_history(int arg, char **argv)
{
	int		max;
	char	*cmd;

	max = 1;
	history(FIRST, NULL, &cmd);
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		max++;
	if (argv[0] && argv[1])
	{
		ft_two_number(arg, argv, max);
		ft_strdel(&argv[0]);
		argv[0] = NULL;
		ft_strdel(&argv[1]);
		argv[1] = NULL;
	}
	else if (argv[0])
	{
		if (ft_strisnbr(argv[0]))
			ft_one_number(arg, argv[0], max);
		else
			ft_dprintf(2, "42sh: fc: %s: numeric argument required\n", argv[0]);
		ft_strdel(&argv[0]);
		argv[0] = NULL;
	}
	else
		ft_no_number(arg, max);
	return (1);
}

static int	opt_arg(int *arg, int opt)
{
	if (opt == 108)
		*arg = *arg | ARG_L;
	else if (opt == 115)
		*arg = *arg | ARG_S;
	else if (opt == 110)
		*arg = *arg | ARG_N;
	else if (opt == 114)
		*arg = *arg | ARG_R;
	else if (opt == 101)
		*arg = *arg | ARG_E;
	return (1);
}

static int	ft_parser(int argc, char **argv, char *optstring, char **option)
{
	static int	index = 1;
	static int	i = 1;
	char		*tmp;
	int			opt;
	int			argv_opt;

	opt = 1;
	(void)option;
	if (argc > 1 && (argc - 1) >= index)
	{
		while (argv[index][0] == '-' && argv[index][i] != '\0' && !ft_strisnbr(argv[index]))
		{
			if (!(tmp = ft_strchr(optstring, argv[index][i])))
			{
				ft_dprintf(2, "42sh: fc: -%c: invalid option\n", argv[index][i]);
				i = 1;
				index = 1;
				return (63);
			}
			else
			{
				i++;
				argv_opt = index;
				while (tmp[opt] == ':')
				{
					argv_opt++;
					if (argv[argv_opt] && ft_strisnbr(argv[argv_opt]))
					{
						if (!(option[opt - 1] = ft_strdup(argv[argv_opt])))
							return (0);
					}
					else
						return (argv[index][i - 1]);
					opt++;
				}
				return (argv[index][i - 1]);
			}
		}
		if (argv[index][0] != '-' && !ft_strisnbr(argv[index]))
			return (63);
		i = 1;
		index++;
		return (1);
	}
	i = 1;
	index = 1;
	return (-1);
}

static int		ft_init_option(char ***option)
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

int		cmd_fc(int argc, char **argv)
{
	char	**option;
	int 	ret;
	int		opt;
	int		arg;
	char	optstring[] = "rnl::s:e::";

	arg = 0;
	if (!ft_init_option(&option))
		return (0);
	while ((opt = ft_parser(argc, argv, optstring, option)) != -1)
	{
		if (opt == 63)/*[?]*/
		{
			ft_dprintf(2, "fc: usage: fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]\n");
			ft_strdel_option(&option);
			return (0);
		}
		else if (opt == 0)
		{
			ft_dprintf(2, "cannot allocate memory\n");
			ft_strdel_option(&option);
			return (0);
		}
		else
			opt_arg(&arg, opt);
	}
	if (arg & ARG_S)
		ret = ft_execute(option);
	else if (arg & ARG_L)
		ret = ft_print_history(arg, option);
	else
		ret = ft_fc();
	ft_strdel_option(&option);
	return (ret);
}
