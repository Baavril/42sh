/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:34:42 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/12 16:27:22 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

extern int	g_retval;

int			ft_atoi_history(const char *str)
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
	execute(input);//double free si la commande n'est pas valide
	ft_strdel(&input);
	update_intern_vars();
	return (1);
}

static int		fc_s_option(char *str_nbr)
{
//	int		nbr;

//	nbr = ft_atoi_history(str_nbr);
	ft_atoi_history(str_nbr);
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

int 		ft_strisnbr(char *str)
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
