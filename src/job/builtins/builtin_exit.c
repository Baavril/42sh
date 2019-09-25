/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:14:19 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "jcont.h"

static int	part_sep(int argc, char **argv)
{
	extern char	**environ;
	unsigned char	status;
	
	status = g_retval;
	if (!ft_strcmp("--", argv[1]))
	{
		if (argc == 2)
		{
			ft_tabdel(&argv);
			ft_tabdel(&environ);
			write(STDOUT_FILENO, "exit\n", 5 * sizeof(char));
			exit(status);
		}
		return (2);
	}
	return (1);
}

static int	numarg_exit(int argc, char **argv, int i)
{
	extern char	**environ;
	unsigned char	status;
	
	status = g_retval;
	write(STDOUT_FILENO, "exit\n", 5 * sizeof(char));
	if (argc > i + 1)
	{
		ft_dprintf(STDERR_FILENO,
		"%s: %s: too many arguments\n",	g_progname, argv[0]);
		return (1);
	}
	status = (unsigned char)ft_atoi(argv[i]);
	ft_tabdel(&argv);
	ft_tabdel(&environ);
	exit(status);
}

static void	nomatter_exit(char **argv, int i)
{
	extern char	**environ;
	
	write(STDOUT_FILENO, "exit\n", 5 * sizeof(char));
	ft_dprintf(STDERR_FILENO,
	"%s: %s: %s: numeric argument required\n",
			g_progname, argv[0], argv[i]);
	ft_tabdel(&argv);
	ft_tabdel(&environ);
	exit(2);
}

int		cmd_exit(int argc, char **argv)
{
	extern char	**environ;
	unsigned char	status;
	int		i;

	status = g_retval;
	if (argc > 1)
	{
		i = part_sep(argc, argv);
		if (*argv[i]
			&& (((*argv[i] == '-' || *argv[i] == '+') && ft_str_is_numeric(&argv[i][i]))
			|| ft_str_is_numeric(argv[i])) && ft_strcmp("--", argv[i]))
			return (numarg_exit(argc, argv, i));
		else
			nomatter_exit(argv, i);
	}
	ft_tabdel(&argv);
	ft_tabdel(&environ);
	exit(status);
}
