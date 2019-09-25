/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/21 14:51:24 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ft_getopt.h"
#include "libft.h"
#include "error.h"
#include "path.h"

static int	parse_opt(int argc, char **argv, _Bool *p)
{
	int	opt;

	*p = 0;
	g_opterr = 1;
	g_optind = 0;
	while ((opt = ft_getopt(argc, argv, "+LP")) != -1)
	{
		if (opt == 'P')
			*p |= 1;
		else if (opt == '?')
		{
			ft_dprintf(STDERR_FILENO, "%1$s: usage: %1$s [-L|-P]\n", argv[0]);
			return (2);
		}
	}
	return (e_success);
}

int	cmd_pwd(int argc, char **argv)
{
	char	*cwd;
	int	ret;
	_Bool	p;

	p = 0;
	ret = 0;
	g_optind = 0;
	if ((ret = parse_opt(argc, argv, &p)))
		return (ret);
	if (p)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (1);
		else
		{
			ft_printf("%s\n", cwd);
			ft_memdel((void**)&cwd);
		}
	}
	else if (*g_pwd)
		ft_printf("%s\n", g_pwd);
	else if	((cwd = ft_getenv("PWD")))
		ft_printf("%s\n", cwd);
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (1);
		else
		{
			ft_printf("%s\n", cwd);
			ft_memdel((void**)&cwd);
		}
	}
	return (0);
}
