/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/08 13:28:00 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** source : https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html
*/

#include <stdlib.h>

#include "libft.h"
#include "builtins.h"
#include "error.h"
#define EXIT_STATUS 127

const t_builtins	g_builtins[] =
{
	{ "alias", &cmd_alias},
	{ "unalias", &cmd_unalias},
	{ "echo", &cmd_echo},
	{ "hash", &cmd_hash},
	{ "exit", &cmd_exit},
	{ "cd", &cmd_cd},
	{ "true", &cmd_true},
	{ "false", &cmd_false},
	{ "type", &cmd_type},
	{ "fg", &cmd_fg},
	{ "bg", &cmd_bg},
	{ "jobs", &cmd_jobs},
	{ "set", &cmd_set},
	{ "setenv", &cmd_setenv},
	{ "unset", &cmd_unset},
	{ "unsetenv", &cmd_unsetenv},
	{ "env", &cmd_env},
	{ "export", &cmd_export},
	{ "\0", NULL}
};

static void			*dispatcher(char *cmd)
{
	int	i;

	i = 0;
	while (g_builtins[i].key[0] && ft_strcmp(cmd, g_builtins[i].key))
		++i;
	if (!(g_builtins[i].key[0]))
		return (NULL);
	else
		return ((void*)g_builtins[i].f);
}

int					is_a_builtin(char *cmd)
{
	if (dispatcher(cmd))
		return (1);
	else
		return (0);
}

int					builtins_dispatcher(char **argv)
{
	int			(*f)(int, char**);
	int			ret;
	int			argc;

	argc = 0;
	ret = EXIT_STATUS;
	if ((f = dispatcher(*argv)))
	{
		while (argv[argc])
			++argc;
		ret = f(argc, argv);
	}
	return (ret);
}
