/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:32:13 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 21:48:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "libft.h"
#include "history.h"
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
/*	extern int	g_fd_prompt;
*/	char		*input;
	char		**args;
	int		status;
	
	(void)argc;
	copybuff = NULL;
	g_progname = argv[0];
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
	set_signals(0);
	while (!read_command(&input) || get_next_line(0, &input))
	{
		if (!((status = history(ADD_CMD, &input, NULL))))
		{	
			psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
			return (1);
		}
		if (status != -1)
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
		else
			ft_memdel((void**)&input);
	}
	history(DELETE, NULL, NULL);
	ft_tabdel(&environ);
	ft_strdel(&copybuff);
	ft_free_bintable();
	return (0);
}