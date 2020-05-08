/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_simple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:43:35 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/07 17:17:30 by tgouedar         ###   ########.fr       */
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
	char	*token;

	if (!(token = ft_strdup(left.c)))
		return (0);
	if (ft_strfchr("HISTFILE=", token) == 1)
		history(NEW_HIST, NULL, NULL);
	expansions_treatment(&(token));
	if (checkvarlst(token))
		setenvnod(newnodshell(token, 0));
	ft_strdel(&token);
	if (right.v)
		right.v->f(right.v->left, right.v->right);
	return (0);
}

int		i_builtin(t_elem left, t_elem right)
{
	g_argv = malloc(sizeof(char *) * TAB_SIZE);
	g_argv[0] = left.c;
	g_argv[1] = NULL;
	if (!right.v || right.v->f(right.v->left, right.v->right) != -1)
		if ((g_retval = builtins_dispatcher(g_argv)) == 127)
			ft_dprintf(STDERR_FILENO, "unknown command : %s\n", g_argv[0]);
	free(g_argv);
	return (g_retval);
}

int		i_exec(t_elem left, t_elem right)
{
	extern char	**environ;

	g_argv = malloc(sizeof(char *) * TAB_SIZE);
	g_argv[0] = left.c;
	g_argv[1] = NULL;
	if (!right.v || right.v->f(right.v->left, right.v->right) != -1)
		execve(g_argv[0], g_argv, environ);
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
	if (*left.c)
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
