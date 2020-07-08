/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_simple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:43:35 by bprunevi          #+#    #+#             */
/*   Updated: 2020/07/07 15:07:38 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "history.h"
#include "builtins.h"
#include "shell_variables.h"
#include "expansions.h"
#include "error.h"
#include "jcont.h"
#include <unistd.h>
#define TAB_SIZE 16

char		**g_argv;
extern int	g_retval;

int		i_prefix(t_elem left, t_elem right)
{
	if (checkvarlst(left.c))
		setenvnod(newnodshell(left.c, 0));
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (0);
}

int		i_builtin(t_elem left, t_elem right)
{
	char	**argv;

	argv = NULL;
	g_argv = malloc(sizeof(char *) * TAB_SIZE);
	g_argv[0] = left.c;
	g_argv[1] = NULL;
	if (((!right.v || right.v->f(right.v->left, right.v->right) != -1))
	&& (argv = g_argv))
		if ((g_retval = builtins_dispatcher(g_argv)) == 127)
			psherror(e_command_not_found, g_argv[0], e_cmd_type);
	free(argv);
	return (g_retval);
}

int		i_exec(t_elem left, t_elem right)
{
	extern char	**environ;

	g_argv = malloc(sizeof(char *) * TAB_SIZE);
	g_argv[0] = left.c;
	g_argv[1] = NULL;
	if (!right.v || right.v->f(right.v->left, right.v->right) != -1)
	{
		if (is_a_builtin(g_argv[0]))
			ft_clean_exit(NULL, builtins_dispatcher(g_argv));
		else
			execve(g_argv[0], g_argv, environ);
	}
	free(g_argv);
	g_retval = 1;
	return (1);
}

char	**realloc_argv(char **argv, size_t i)
{
	char **tmp_argv;

	tmp_argv = malloc(sizeof(char *) * i);
	ft_memcpy(tmp_argv, argv, sizeof(char *) * (i - TAB_SIZE));
	free(argv);
	return (tmp_argv);
}

int		i_suffix_word(t_elem left, t_elem right)
{
	size_t i;

	i = 0;
	if (left.c)
	{
		while (g_argv[++i])
			(void)i;
		if (!((i + 1) % TAB_SIZE))
			g_argv = realloc_argv(g_argv, (i + 1) + TAB_SIZE);
		g_argv[i] = left.c;
		g_argv[++i] = NULL;
	}
	if (right.v)
		return (right.v->f(right.v->left, right.v->right));
	return (0);
}
