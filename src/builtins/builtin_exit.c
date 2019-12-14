/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 21:51:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "history.h"
#include "builtins.h"
#include "libft.h"
#include "shell_variables.h"
#include "error.h"
#include "jcont.h"

struct s_svar *g_svar;

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
			ft_dprintf(STDERR_FILENO, "exit\n");
			history(DELETE, NULL, NULL);
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
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (argc > i + 1)
	{
		ft_dprintf(STDERR_FILENO,
		"%s: %s: too many arguments\n",	g_progname, argv[0]);
		return (1);
	}
	status = (unsigned char)ft_atoi(argv[i]);
	history(DELETE, NULL, NULL);
	ft_tabdel(&argv);
	ft_tabdel(&environ);
	exit(status);
}

static void	nomatter_exit(char **argv, int i)
{
	extern char	**environ;
	
	ft_dprintf(STDERR_FILENO, "exit\n");
	ft_dprintf(STDERR_FILENO,
	"%s: %s: %s: numeric argument required\n",
			g_progname, argv[0], argv[i]);
	history(DELETE, NULL, NULL);
	ft_tabdel(&argv);
	ft_tabdel(&environ);
	exit(2);
}

static void	ft_free_internvars(void)
{
	/* need to be tested when interpreter is done */
	struct s_svar *tmp;

	tmp = NULL;
	while (g_svar)
	{
		tmp = g_svar->next;
		ft_strdel(&(g_svar->str));
		ft_strdel(&(g_svar->key));
		ft_strdel(&(g_svar->value));
		g_svar = tmp;
	}
	free(g_svar);
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
	history(DELETE, NULL, NULL);
	ft_free_bintable();
	ft_free_internvars();
	exit(status);
}
