/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:32:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/02/29 19:08:45 by tgouedar         ###   ########.fr       */
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

int					g_ppid;
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

	g_ppid = getppid();
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

static int	alloc_error(void)
{
	psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
	return (1);
}

int			main(int argc, char **argv)
{
	char			*input;
	int				status;

	(void)argc;
	g_progname = argv[0];
	if (ft_shell_init() == e_cannot_allocate_memory)
		return (alloc_error());
	while (!read_command(&input) || get_next_line(0, &input))
	{
		g_alias_treated = 0;
		if (!(status = history(ADD_CMD, &input, NULL)))
			return (alloc_error());
		if (status != -1 && input[0])
			execute(input);
		ft_check_bgstatus();
		ft_strdel(&input);
		update_intern_vars();
		if (getppid() != g_ppid)
			break ;
	}
	return (cmd_exit(0, NULL));
}
