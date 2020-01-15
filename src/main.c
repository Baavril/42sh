/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:32:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/15 15:48:09 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "libft.h"
#include "shell_variables.h"
#include "history.h"
#include "sig_handler.h"
#include "expansions.h"
#include "builtins.h"
#include "prompt.h"
#include "input.h"
#include "termcaps.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "jcont.h"
#include "synt.h"
#include "path.h"

int					g_retval;
char				g_pwd[] = {0};
struct termios		g_old_termios;

static int	set_minimal_env(void)
{
	char	*tmp;
	int		shlvl;

	tmp = getcwd(NULL, 0);
	if (ft_setenv("PWD", tmp, 1))
		return (e_cannot_allocate_memory);
	ft_memdel((void**)&tmp);
	if (!(tmp = ft_getenv("SHLVL")))
	{
		if (ft_setenv("SHLVL", "1", 1))
			return (e_cannot_allocate_memory);
	}
	else
	{
		shlvl = ft_atoi(tmp) + 1;
		tmp = ft_itoa(shlvl);
		if (ft_setenv("SHLVL", tmp, 1))
			return (e_cannot_allocate_memory);
		ft_memdel((void**)&tmp);
	}
	if (PATH_MAX > 0)
	{
		tmp = ft_getenv("PWD");
		if (ft_strlen(tmp) <= PATH_MAX)
			ft_strcpy(g_pwd, ft_getenv("PWD"));
	}
	return (e_success);
}

int		main(int argc, char **argv)
{
	extern char		**environ;
	char			*input;
	int				status;

	(void) argc;
	set_termcaps(TC_SAVE);
	tcsetpgrp(STDIN_FILENO, getpid()); //Control the terminal
	set_signals(FATHER);
	copybuff = NULL;
	input = NULL;
	g_progname = argv[0];
	init_shellvars(environ);
	/* cmd_set(argc, argv); to show the list of internvars */
	if (!(history(INIT, NULL, NULL)))
		return (1);
	if (!(environ = ft_tabcpy(environ)))
	{
		psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
		return (1);
	}
	g_retval = e_success;
	if ((g_retval = set_minimal_env()))
	{
		psherror(g_retval, argv[0], e_cmd_type);
		ft_tabdel(&environ);
		return (1);
	}
	while (!read_command(&input) || get_next_line(0, &input))
	{
		if (!(status = history(ADD_CMD, &input, NULL)))
		{
			psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
			return (1);
		}
		if (status != -1 && input[0])
		{
			lexer_verbose(&input);
			execute(input);
		}
		ft_strdel(&input);
	}
	cmd_exit(0, NULL);
	return(0);
}
