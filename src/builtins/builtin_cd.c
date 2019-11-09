/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/09/25 16:32:34 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** https://www.unix.com/man-page/posix/1posix/cd/
*/

#include <unistd.h>
#include <sys/stat.h>

#include "ft_getopt.h"
#include "libft.h"
#include "error.h"
#include "path.h"

extern char	g_pwd[];

static int	set_oldpwd(void)
{
	char	*cwd;
	_Bool	allocated;

	allocated = 0;
	if (!(cwd = g_pwd))
	{
		allocated = 1;
		if (!(cwd = getcwd(NULL, 0)))
			return (e_system_call_error);
	}
	if (ft_setenv("OLDPWD", cwd, 1))
	{
		if (allocated)
			ft_memdel((void**)&cwd);
		return (e_cannot_allocate_memory);
	}
	if (allocated)
		ft_memdel((void**)&cwd);
	return (0);
}

static int	refresh_pwd(const char *path, _Bool p)
{
	char	*cwd;

	if (p)
	{
		if (!(cwd = getcwd(NULL, 0)))
			return (e_system_call_error);
		if (ft_setenv("PWD", cwd, 1))
			return (e_cannot_allocate_memory);
		ft_bzero((void*)g_pwd, sizeof(g_pwd));
		ft_strncpy(g_pwd, cwd, sizeof(g_pwd));
		ft_memdel((void**)&cwd);
	}
	else
	{
		if (ft_setenv("PWD", path, 1))
			return (e_cannot_allocate_memory);
		ft_bzero((void*)g_pwd, sizeof(g_pwd));
		ft_strncpy(g_pwd, path, sizeof(g_pwd));
	}
	return (0);
}

static int	change_dir(const char *path, _Bool p)
{
	int	ret;

	if (chdir(path))
		return (e_invalid_input);
	if ((ret = set_oldpwd()))
		return (ret);
	if ((ret = refresh_pwd(path, p)))
		return (ret);
	return (e_success);
}

static int	concatenable_operand(const char *str)
{
	if (*str == '.')
	{
		++str;
		if (*str == '.')
		{
			++str;
			while (*str)
			{
				if (*str != '/')
					return (1);
				++str;
			}
			return (0);
		}
		else
		{
			while (*str)
			{
				if (*str != '/')
					return (1);
				++str;
			}
			return (0);
		}
	}
	while (*str)
	{
		if (*str != '/')
			return (1);
		++str;
	}
	return (0);
}

static int	cdpath_concat(char **path)
{
	char	*beg;
	char	*env;
	char	*dir;
	char	*pathname;

	if (!(beg = ft_getenv("CDPATH")))
		return (e_success);
	if (!(env = ft_strdup(beg)))
		return (e_cannot_allocate_memory);
	beg = env;
	while ((dir = ft_strsep(&env, ":")))
	{
		if (!(pathname = ft_strnjoin(3, dir, "/", *path)))
			return (e_cannot_allocate_memory);
		if (!access(pathname, F_OK))
			break;
		ft_memdel((void**)&pathname);
	}
	ft_memdel((void**)&beg);
	if (dir)
	{
		ft_memdel((void**)path);
		*path = pathname;
		return (3);
	}
	return (e_success);
}

static int	parse_opt(int argc, char **argv, _Bool *p)
{
	int	opt;

	*p = 0;
	g_opterr = 1;
	g_optind = RESET_OPTIND;
	while ((opt = ft_getopt(argc, argv, "+LP")) != -1)
	{
		if (opt == 'P')
			*p |= 1;
		else if (opt == '?')
		{
			ft_dprintf(STDERR_FILENO, "%1$s: usage: %1$s [-L|-P] [dir]\n", argv[0]);
			return (2);
		}
	}
	return (e_success);
}

int		cmd_cd(int argc, char **argv)
{
	struct stat buf;
	char	*path;
	char	*oldpwd;
	char	*tmp;
	int	ret;
	_Bool	p;

	path = NULL;
	
	/* Parse options */
	if ((ret = parse_opt(argc, argv, &p)))
		return (ret);
	/* Set full path for the changedir call  */
	if (!argv[g_optind])
	{
		if (!(path = ft_getenv("HOME")))
			if (!(path = ft_getenv("PWD")))
				return (1);
		if (p)
			path = ft_realpath(path, NULL);
		else
			path = ft_strdup(path);
	}
	else if (!ft_strcmp(argv[g_optind], "-"))
	{
		if (!(oldpwd = ft_getenv("OLDPWD")))
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: OLDPWD not set\n", g_progname, argv[0]);
			g_optind = RESET_OPTIND;
			return (e_invalid_input);
		}
		if (p)
		{
			oldpwd = ft_realpath(oldpwd, NULL);
			path = oldpwd;
		}
		else
			path = ft_strdup(oldpwd);
		ft_printf("%s\n", path);
	}
	else if (*(argv[g_optind]) == '/')
		path = ft_strdup(argv[g_optind]);
	else if (concatenable_operand(argv[g_optind]))
	{
		path = ft_strdup(argv[g_optind]);
		if ((ret = cdpath_concat(&path)) == e_cannot_allocate_memory)
			return (g_errordesc[e_cannot_allocate_memory].code);
		else if (ret == 3)
			ft_printf("%s\n", path);
		else
		{
			tmp = path;
			path = ft_strnjoin(3, g_pwd, "/", tmp);
			ft_memdel((void**)&tmp);
		}
		ret = e_success;
	}
	else
	{
		path = ft_strdup(argv[g_optind]);
		tmp = path;
		path = ft_strnjoin(3, g_pwd, "/", tmp);
		ft_memdel((void**)&tmp);
	}
	
	/* Resolve path */
	if (!access(path, F_OK))
		path = ft_resolvepath(path);
	if (!path)
		return (1);

	/* Control access */
	if (stat(path, &buf))
	{
		if (!argv[g_optind] || !*argv[g_optind])
		{
			ft_dprintf(STDERR_FILENO,
			"%s: %s: %s: No such file or directory\n",
			g_progname, argv[0], path);
		}
		else
		{
			ft_dprintf(STDERR_FILENO,
			"%s: %s: %s: No such file or directory\n",
			g_progname, argv[0], argv[g_optind]);
		}
		ft_memdel((void**)&path);
		return (1);
	}
	if (access(path, F_OK))
	{
		ft_dprintf(STDERR_FILENO,
		"%s: %s: %s: Permission denied\n",
		g_progname, argv[0], argv[g_optind]);
		ft_memdel((void**)&path);
		return (1);
	}

	/* Execute changedir */
	if ((ret = change_dir(path, p)))
	{
		if (ret != e_invalid_input)
		{
			psherror(ret, argv[0], e_cmd_type);
			ft_memdel((void**)&path);
			return (g_errordesc[ret].code);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n",
			g_progname, argv[0], path, g_errordesc[e_no_such_file_or_directory].message);
			ft_memdel((void**)&path);
			return (e_invalid_input);
		}
	}
	ft_memdel((void**)&path);
	return (ret);
}
