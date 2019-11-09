/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:13:47 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ft_errno.h"
#include "error.h"
#include "libft.h"

static char	**getenvvar(const char *name)
{
	extern char **environ;
	int			i;
	int			j;

	if (name)
	{
		i = 0;
		while (environ[i])
		{
			j = 0;
			while (name[j] && environ[i][j] && name[j] == environ[i][j])
				++j;
			if (environ[i][j] != '=' || name[j])
				++i;
			else
			{
				++j;
				return (&environ[i]);
			}
		}
	}
	return (NULL);
}

static int		ft_unset_alloc_env(const char *name)
{
	extern char	**environ;
	char		**dst;
	char		**src;
	int		tlen;

	if (!name || !*name || ft_strstr(name, "="))
	{
		g_errno = E_EINVAL;
		return (-1);
	}
	else
	{
		if (!(dst = getenvvar(name)))
			return (0);
		ft_memdel((void**)dst);
		src = dst + 1;
		tlen = ft_tablen(src);
		ft_memmove(dst, src, sizeof(char*) * tlen);
		dst[tlen] = NULL;
		return (0);
	}
}

int		cmd_unsetenv(int argc, char **argv)
{
	if (argc != 2)
	{
		psherror(e_invalid_input, argv[0], e_cmd_type);
		ft_dprintf(STDERR_FILENO, "Usage: %s VAR [VALUE]\n", argv[0]);
		return (g_errordesc[e_invalid_input].code);
	}
	else
	{
		if (ft_unset_alloc_env(argv[1]))
		{
			ft_perror(NULL);
			return (1);
		}
		else
			return (0);
	}
}
