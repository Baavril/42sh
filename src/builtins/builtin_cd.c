#include <unistd.h>
#include <sys/stat.h>

#include "ft_getopt.h"
#include "libft.h"
#include "error.h"
#include "path.h"

extern char		*g_progname;
extern int		g_optind;
extern int		g_opterr;
extern int		g_optopt;

static int		ft_update_pwd(char *new_pwd, char flag)
{
	char	*old_pwd;
	char	pwd[PATH_MAX];


	if (chdir(new_pwd) == -1)
	{
		if (!(flag))
			free(new_pwd);
		return (TARGET_NOT_FOUND);
	}
	old_pwd = ft_get_env_var("PWD");
	ft_set_env_var("OLDPWD", old_pwd);
	getcwd(pwd, PATH_MAX);
	ft_set_env_var("PWD", pwd);
	free(new_pwd);
	free(old_pwd);
	return (EXEC_SUCCESS);
}
/*
static int		ft_treat_path(char *new_pwd, int opt_p)
{
	if (!new_pwd)
		return (ERROR);
	if (*new_pwd != '/')
	{
		if (new_pwd[0] == '.'
		&& (new_pwd[1] == '/' || (new_pwd[1] == '.' && new_pwd[2] == '/')))
			concatenate(PWD, new_pwd);
//		else if (getenv(CD_PATH))
//		{
//			split = ft_str_split(CD_PATH);
//			while (split++)
//			{
//				concatenate(*split, new_pwd)
//				//if (is_valid_dir())
//					break ;
//			}
		}
	}
	if (!opt_p)
		simplify_path();
	if (!have_acces_right(new_pwd))
		Pemission denied/is file;
	return (ft_update_pwd());
}
	*/
static int		ft_cd_exec(char *new_pwd, int opt_p)
{
	int		ret;
	char	*target;

	if (!(new_pwd))
	{
		if (!(target = ft_get_env_var("HOME")))
		{
			ft_dprintf(STDERR_FILENO, "%s: cd: HOME not set.\n", g_progname);
			return (UNSET_VAR);
		}
		ret = ft_check_target(target);
	}
	if (!(ft_strcmp(new_pwd, "-")))
	{
		if (!(target = ft_get_env_var(env, "OLDPWD")))
		{
			ft_dprintf(STDERR_FILENO, "%s: cd: OLDPWD not set.\n", g_progname);
			return (UNSET_VAR);
		}
		if ((ret = ft_check_target(target)) == EXEC_SUCCESS)
			ft_putendl(target);
	}
	else if (target = ft_strdup(new_pwd))
		ret = ft_check_target(target);
	return (ret);
}

static int		parse_opt(int argc, char **argv, int *p)
{
	int		opt;

	*p = 0;
	g_opterr = 1;
	g_optind = RESET_OPTIND;
	while ((opt = ft_getopt(argc, argv, CD_OPT)) != -1)
	{
		if (opt == 'P')
			*p |= 1;
		else if (opt == '?')
		{
			ft_dprintf(STDERR_FILENO, "cd: usage: cd [-L|-P] [dir].\n");
			return (2);
		}
	}
	return (0);
}

int				cmd_cd(int ac, char **av)
{
	int		opt_p;
	int		ret;
	char	*var_value;

	if ((ret = ft_parse_cd_opt(ac, av, &opt_p)))
		return (ret);
	if (ret = ft_cd_exec(av[g_optind]) == EXEC_SUCCESS);
	{
		if (!av[g_optind] || !ft_strcmp("-", av[g_optind]))
			var_value = "cd";
		else
			var_value = av[g_optind]
				ft_set_env_var("_", var_value);
	}
	return (ret);
}





//
//static int		concatenable_operand(const char *str)
//{
//	if (*str == '.')
//	{
//		++str;
//		if (*str == '.')
//		{
//			++str;
//			while (*str)
//			{
//				if (*str != '/')
//					return (1);
//				++str;
//			}
//			return (0);
//		}
//		else
//		{
//			while (*str)
//			{
//				if (*str != '/')
//					return (1);
//				++str;
//			}
//			return (0);
//		}
//	}
//	while (*str)
//	{
//		if (*str != '/')
//			return (1);
//		++str;
//	}
//	return (0);
//}
//
//static int		cdpath_concat(char **path)
//{
//	char	*beg;
//	char	*env;
//	char	*dir;
//	char	*pathname;
//
//	if (!(beg = ft_getenv("CDPATH")))
//		return (e_success);
//	if (!(env = ft_strdup(beg)))
//		return (e_cannot_allocate_memory);
//	beg = env;
//	while ((dir = ft_strsep(&env, ":")))
//	{
//		if (!(pathname = ft_strnjoin(3, dir, "/", *path)))
//			return (e_cannot_allocate_memory);
//		if (!access(pathname, F_OK))
//			break;
//		ft_memdel((void**)&pathname);
//	}
//	ft_memdel((void**)&beg);
//	if (dir)
//	{
//		ft_memdel((void**)path);
//		*path = pathname;
//		return (3);
//	}
//	return (e_success);
//}
//
//static int		parse_opt(int argc, char **argv, _Bool *p)
//{
//	int		opt;
//
//	*p = 0;
//	g_opterr = 1;
//	g_optind = RESET_OPTIND;
//	while ((opt = ft_getopt(argc, argv, "+LP")) != -1)
//	{
//		if (opt == 'P')
//			*p |= 1;
//		else if (opt == '?')
//		{
//			ft_dprintf(STDERR_FILENO, "%1$s: usage: %1$s [-L|-P] [dir]\n", argv[0]);
//			return (2);
//		}
//	}
//	return (e_success);
//}
//
//int				cmd_cd(int argc, char **argv)
//{
//	struct stat		buf;
//	char			*path;
//	char			*oldpwd;
//	char			*tmp;
//	int				ret;
//	_Bool			p;
//
//	path = NULL;
//	/* Parse options */
//	if ((ret = parse_opt(argc, argv, &p)))
//		return (ret);
//	/* Set full path for the changedir call  */
//	if (!argv[g_optind])
//	{
//		if (!(path = ft_getenv("HOME")))
//			if (!(path = ft_getenv("PWD")))
//				return (1);
//		if (p)
//			path = ft_realpath(path, NULL);
//		else
//			path = ft_strdup(path);
//	}
//	else if (!ft_strcmp(argv[g_optind], "-"))
//	{
//		if (!(oldpwd = ft_getenv("OLDPWD")))
//		{
//			ft_dprintf(STDERR_FILENO, "%s: %s: OLDPWD not set\n", g_progname, argv[0]);
//			g_optind = RESET_OPTIND;
//			return (e_invalid_input);
//		}
//		if (p)
//		{
//			oldpwd = ft_realpath(oldpwd, NULL);
//			path = oldpwd;
//		}
//		else
//			path = ft_strdup(oldpwd);
//		ft_printf("%s\n", path);
//	}
//	else if (*(argv[g_optind]) == '/')
//		path = ft_strdup(argv[g_optind]);
//	else if (concatenable_operand(argv[g_optind]))
//	{
//		path = ft_strdup(argv[g_optind]);
//		if ((ret = cdpath_concat(&path)) == e_cannot_allocate_memory)
//			return (g_errordesc[e_cannot_allocate_memory].code);
//		else if (ret == 3)
//			ft_printf("%s\n", path);
//		else
//		{
//			tmp = path;
//			path = ft_strnjoin(3, g_pwd, "/", tmp);
//			ft_memdel((void**)&tmp);
//		}
//		ret = e_success;
//	}
//	else
//	{
//		path = ft_strdup(argv[g_optind]);
//		tmp = path;
//		path = ft_strnjoin(3, g_pwd, "/", tmp);
//		ft_memdel((void**)&tmp);
//	}
//	
//	/* Resolve path */
//	if (!access(path, F_OK))
//		path = ft_resolvepath(path);
//	if (!path)
//		return (1);
//
//	/* Control access */
//	if (stat(path, &buf))
//	{
//		if (!argv[g_optind] || !*argv[g_optind])
//		{
//			ft_dprintf(STDERR_FILENO,
//			"%s: %s: %s: No such file or directory\n",
//			g_progname, argv[0], path);
//		}
//		else
//		{
//			ft_dprintf(STDERR_FILENO,
//			"%s: %s: %s: No such file or directory\n",
//			g_progname, argv[0], argv[g_optind]);
//		}
//		ft_memdel((void**)&path);
//		return (1);
//	}
//	if (access(path, F_OK))
//	{
//		ft_dprintf(STDERR_FILENO,
//		"%s: %s: %s: Permission denied\n",
//		g_progname, argv[0], argv[g_optind]);
//		ft_memdel((void**)&path);
//		return (1);
//	}
//
//	/* Execute changedir */
//	if ((ret = change_dir(path, p)))
//	{
//		if (ret != e_invalid_input)
//		{
//			psherror(ret, argv[0], e_cmd_type);
//			ft_memdel((void**)&path);
//			return (g_errordesc[ret].code);
//		}
//		else
//		{
//			ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n",
//			g_progname, argv[0], path, g_errordesc[e_no_such_file_or_directory].message);
//			ft_memdel((void**)&path);
//			return (e_invalid_input);
//		}
//	}
//	ft_memdel((void**)&path);
//	return (ret);
//}
