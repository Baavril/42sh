/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:49:03 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:01:50 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "ft_errno.h"

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

#ifdef FT_ERRNO_H

int			ft_unsetenv(const char *name)
{
	extern char	**environ;
	char		**dst;
	char		**src;
	int			tlen;

	if (!name || !*name || ft_strstr(name, "="))
	{
		g_errno = E_EINVAL;
		return (-1);
	}
	else
	{
		if (!(dst = getenvvar(name)))
			return (0);
		src = dst + 1;
		tlen = ft_tablen(src);
		ft_memmove(dst, src, sizeof(char*) * tlen);
		dst[tlen] = NULL;
		return (0);
	}
}

#else

int			ft_unsetenv(const char *name)
{
	extern char	**environ;
	char		**dst;
	char		**src;
	int			tlen;

	if (!name || !*name || ft_strstr(name, "="))
		return (-1);
	else
	{
		if (!(dst = getenvvar(name)))
			return (0);
		src = dst + 1;
		tlen = ft_tablen(src);
		ft_memmove(dst, src, sizeof(char*) * tlen);
		dst[tlen] = NULL;
		return (0);
	}
}

#endif
