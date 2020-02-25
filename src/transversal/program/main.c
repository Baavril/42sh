/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:32:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/02/25 11:18:19 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "shell_variables.h"
#include "sig_handler.h"
#include "expansions.h"
#include "termcaps.h"
#include "builtins.h"
#include "history.h"
#include "prompt.h"
#include "parser.h"
#include "input.h"
#include "libft.h"
#include "error.h"
#include "lexer.h"
#include "jcont.h"
#include "synt.h"
#include "path.h"

int					g_retval;
extern int			g_alias_treated;
struct termios		g_old_termios;

static int	set_minimal_env(void)
{
	char	*tmp;
	int		shlvl;

	tmp = getcwd(NULL, 0);
	if (ft_setenv("PWD", tmp))
		return (e_cannot_allocate_memory);
	ft_memdel((void**)&tmp);
	if (!(tmp = ft_getenv("SHLVL")))
	{
		if (ft_setenv("SHLVL", "1"))
			return (e_cannot_allocate_memory);
	}
	else
	{
		shlvl = ft_atoi(tmp) + 1;
		ft_strdel(&tmp);
		tmp = ft_itoa(shlvl);
		if (ft_setenv("SHLVL", tmp))
			return (e_cannot_allocate_memory);
		ft_memdel((void**)&tmp);
	}
	return (e_success);
}

static int	ft_shell_init(void)
{
	extern char		**environ;

	set_termcaps(TC_SAVE);
	tcsetpgrp(STDIN_FILENO, getpid());
	set_signals(FATHER);
	if (!(environ = ft_tabcpy(environ)))
		return (e_cannot_allocate_memory);
	g_retval = e_success;
	if ((set_minimal_env()))
	{
		ft_tabdel(&environ);
		return (e_cannot_allocate_memory);
	}
	init_shell_vars(environ);
	if (!(history(INIT, NULL, NULL)))
		return (1);
	return (0);
}

int			main(int argc, char **argv)
{
	char			*input;
	int				status;

	(void) argc;
	g_progname = argv[0];
	if (ft_shell_init() == e_cannot_allocate_memory)
	{
		psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
		return (1);
	}
	while (!read_command(&input) || get_next_line(0, &input))
	{
		g_alias_treated = 0;
		if (!(status = history(ADD_CMD, &input, NULL)))
		{
			psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
			return (1);
		}
		if (status != -1 && input[0])
		{
			//lexer_verbose(&input);
			execute(input);
			ft_check_bgstatus();
		}
		ft_strdel(&input);
		update_intern_vars();
	}
	cmd_exit(0, NULL);
	return (0);
}
