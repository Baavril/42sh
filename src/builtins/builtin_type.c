/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/19 14:27:53 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "hash_module.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"
#include "job.h"

static const struct s_keywords		g_keywords[] =
{
	{ "{" },
	{ "}" },
	{ "!" },
	{ "do" },
	{ "if" },
	{ "fi" },
	{ "for" },
	{ "case" },
	{ "esac" },
	{ "then" },
	{ "else" },
	{ "done" },
	{ "until" },
	{ "while" },
	{ "select" },
	{ "function" },
	{ NULL }
};

static _Bool						is_a_keyword(char *word)
{
	int		i;

	i = 0;
	while (g_keywords[i].keyword)
	{
		if (!ft_strcmp(g_keywords[i].keyword, word))
			return (1);
		else
			++i;
	}
	return (0);
}

static char							*getbinpath(char *bin)
{
	char	*cpy;

	if (!(cpy = ft_strdup(bin)))
		return (NULL);
	if (path_concat(&cpy) == e_success)
		return (cpy);
	else
	{
		ft_memdel((void**)&cpy);
		return (NULL);
	}
}

static int							ft_parse_type_arg(char *arg)
{
	int		found;
	char	*str;

	found = 0;
	str = NULL;
	if (is_a_builtin(arg))
		ft_printf("%s is a shell builtin.\n", arg);
	else if (is_a_keyword(arg))
		ft_printf("%s is a shell keyword.\n", arg);
	else if ((ft_inbintable(arg, &str, NO_HIT)))
		ft_printf("%s is hashed (%s).\n", arg, str);
	else if ((str = ft_get_alias(arg)))
		ft_printf("%s is aliased to `%s'.\n", arg, str);
	else if ((str = getbinpath(arg)))
		ft_printf("%s is %s.\n", arg, str);
	else
		found = 1;
	if ((str))
		ft_memdel((void**)&str);
	return (found);
}

int									cmd_type(int argc, char **argv)
{
	_Bool	error;
	int		i;

	i = 1;
	error = 0;
	while (i < argc)
	{
		if (ft_parse_type_arg(argv[i]))
		{
			error = 1;
			ft_dprintf(STDERR_FILENO,
					"%s: type: %s: not found.\n", g_progname, argv[i]);
		}
		++i;
	}
	return (error);
}
