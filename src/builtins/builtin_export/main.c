/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by bprunev           #+#    #+#             */
/*   Updated: 2020/01/19 13:18:48 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell_variables.h"
#include "builtins.h"
#include "builtin_export.h"
#include "libft.h"

extern struct s_svar	*g_svar;

void					ft_prtsrtlst(void)
{
	struct s_svar	*tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (g_svar->exp == 1)
			ft_printf("export %s\"%s\"\n", g_svar->key, g_svar->value);
		g_svar = g_svar->next;
	}
	g_svar = tmp;
}

int						export_opt(char *opt)
{
	if (ft_strcmp(opt, "-p") == 0 || ft_strcmp(opt, "--") == 0)
	{
		ft_prtsrtlst();
		return (SUCCESS);
	}
	ft_printf("21sh: export: %s: invalid option\nexport: usage: export -p\n",
	opt);
	return (2);
}

static int				dispatcher_export(char *argv, int flag)
{
	extern char	**environ;

	if (ft_strchr(argv, '='))
	{
		if (checkvarlst(argv) == ERROR)
		{
			setenvnod(newnodshell(argv, flag));
			if (flag)
			{
				if (!(environ = realloc_environ(environ, argv)))
					return (ERROR);
			}
		}
	}
	else
	{
		if (!(environ = ft_check_ifset(argv, environ)))
			return (ERROR);
	}
	return (SUCCESS);
}

int						cmd_export(int argc, char **argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	(void)argc;
	if (ft_strcmp(argv[i], "export") == 0)
	{
		(argv[i + 1]) ? i++ : ft_prtsrtlst();
		flag = 1;
	}
	while (argv[i])
	{
		if (flag == 1 && argv[i][0] == '-' && ft_tablen(argv) == 2)
			return (export_opt(argv[i]));
		dispatcher_export(argv[i], flag);
		++i;
	}
	return (SUCCESS);
}
