/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_simple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:43:35 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/27 14:38:31 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"
#include "shell_variables.h"
#include "error.h"
#include <unistd.h>

char **g_argv;

int	i_prefix(t_elem left, t_elem right)
{
	listadd_back(newnodshell(left.c, 0));
	cmd_set(0, NULL);
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (0);
}

int	i_builtin(t_elem left, t_elem right)
{
	g_argv = malloc(sizeof(char *) * 16); //16 ARGS MAX, NON
	g_argv[0] = left.c;
	g_argv[1] = NULL;
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (builtins_dispatcher(g_argv));
}

int	i_exec(t_elem left, t_elem right)
{
	extern char **environ;

	g_argv = malloc(sizeof(char *) * 16); //16 ARGS MAX, NON
	g_argv[0] = left.c;
	g_argv[1] = NULL;
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	if (eval_command(g_argv))
		exit(ft_dprintf(1, "unknown command : %s\n", g_argv));
	else
		return (execve(g_argv[0], g_argv, environ));
}

int	i_suffix_word(t_elem left, t_elem right)
{
	int i;

	i = 0;
	while (g_argv[++i])
		(void)i;
	g_argv[i] = left.c;
	g_argv[++i] = NULL;
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (0);
}

int	i_suffix_redirect(t_elem left, t_elem right)
{
	left.v->f(left.v->left, left.v->right);
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (0);
}
