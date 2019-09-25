/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:32:13 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/21 15:09:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "libft.h"
#include "sig_handler.h"
#include "builtins.h"
#include "prompt.h"
#include "input.h"
#include "error.h"
#include "lexer.h"
#include "jcont.h"
#include "synt.h"
#include "path.h"

int		g_retval;
char	g_pwd[] = {0};

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
	extern char	**environ;
	extern int	g_fd_prompt;
	char		*input;
	char		**args;
	int		status;
	
	(void)argc;
	status = 0;
	g_progname = argv[0];
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
	set_signals(0);
	if ((g_fd_prompt = initialize_prompt_fd()) == -1)
	{
		ft_tabdel(&environ);
		return (2);
	}
	while (prompt_display(g_retval) && get_stdin(&input) >= 0)
	{
		args = lexer(&input);
		ft_memdel((void**)&input);
		if (!args)
			continue;
		status = synt(args);
		if (status != e_success)
		{
			g_retval = status;
			ft_tabdel(&args);
			continue;
		}
		g_retval = jcont(args, environ);
		ft_tabdel(&args);
	}
	ft_tabdel(&environ);
	return (0);
}
