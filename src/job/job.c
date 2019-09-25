/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:03:13 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/21 16:20:30 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "sig_handler.h"
#include "builtins.h"
#include "error.h"
#include "libft.h"
#include "job.h"

pid_t		g_childpid = 0;

static int 	check_type(char **arg)
{
	struct stat	buf;
	char		*pathname;

	buf = (struct stat){.st_mode = 0};
	pathname = *arg;
	if (prior_builtin(*arg))
	{
		ft_memdel((void**)arg);
		return (e_command_not_found);
	}
	if (!ft_strcmp(*arg, "."))
		return (e_filename_arg_required);
	if (ft_strstr(*arg, "/"))
	{
		if (access(*arg, F_OK))
			return (e_no_such_file_or_directory);
		else if (stat(*arg, &buf))
			return (e_system_call_error);
	}
	else
	{
		if (path_concat(arg))
			*arg = pathname;
		if (stat(*arg, &buf))
			return (e_command_not_found);
	}
	return (e_success);
}

static int	check_access(char *arg)
{
	int ret;

	ret = e_success;
	if ((ret = access(arg, X_OK)))
	{
		psherror(e_permission_denied, arg, e_cmd_type);
		return (e_permission_denied);
	}
	return (e_success);
}

static int	builtin_keyword_exec(char **argv)
{
	int	ret;

	ret = e_success;
	if (argv[1] && (ret = builtins_dispatcher(&argv[1])) != e_command_not_found)
	{
		return (ret);
	}
	else
	{
		psherror(e_no_builtin, argv[1], e_cmd_type);
		return (g_errordesc[e_no_builtin].code);
	}
}

static int	process_launch(char **argv, char **envp, char *pathname)
{
	extern pid_t	g_childpid;
	int		wstatus;
	int		ret;

	wstatus = 0;
	ret = e_success;
	ft_swap((void**)&argv[0], (void**)&pathname);

	if ((g_childpid = fork()) == 0) /*add fork protection, check SHLVL and resources */
	{
		ret = execve(pathname, argv, envp);
		ft_tabdel(&argv);
		ft_tabdel(&envp);
		ft_memdel((void**)&pathname);
		exit (ret);
	}
	else
	{
		set_signals(1);
		waitpid(g_childpid, &wstatus, WUNTRACED);
		ret = WEXITSTATUS(wstatus);
		ft_memdel((void**)&pathname);
		return (ret);
	}
}

int	job(char **argv, char **envp)
{
	int	ret;
	char	*pathname;

	ret = e_success;
	if (!ft_strcmp(argv[0], "builtin"))
		return (builtin_keyword_exec(argv));
	pathname = ft_strdup(argv[0]);
	if ((ret = check_type(&argv[0])) != e_command_not_found && ret != e_success) /* check type of the argument */
	{
		psherror(ret, pathname, e_cmd_type);
		ft_memdel((void**)&pathname);
		return (g_errordesc[ret].code);
	}
	if (ret == e_success)
	{
		if (!check_access(argv[0]))
			return (process_launch(argv, envp, pathname));
		else
		{
			ft_memdel((void**)&pathname);
			return (g_errordesc[e_permission_denied].code);
		}
	}
	else
	{
		argv[0] = pathname;
		ret = builtins_dispatcher(&argv[0]);
	   	if (ret == e_command_not_found)
		{
			psherror(e_command_not_found, argv[0], e_cmd_type);
			return (g_errordesc[e_command_not_found].code);
		}
		return (ret);
	}
}
