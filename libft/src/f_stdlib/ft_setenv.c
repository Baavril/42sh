/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:49:03 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/06 15:56:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

static void	append_environ(const char *name, const char *value)
{
	extern char	**environ;
	char		**new_env;
	char		*tmp;
	int			nb;

	nb = 0;
	new_env = NULL;
	while (environ[nb])
		++nb;
	new_env = (char**)ft_memalloc(sizeof(char**) * (nb + 2));
	--nb;
	while (nb >= 0)
	{
		new_env[nb + 1] = environ[nb];
		--nb;
	}
	new_env[0] = (char*)ft_memalloc(ft_strlen(name) + 1 + ft_strlen(value));
	tmp = ft_strendcpy(new_env[0], name);
	tmp = ft_strendcpy(tmp, "=");
	tmp = ft_strendcpy(tmp, value);
	free(environ);
	environ = new_env;
}

int			ft_setenv(const char *name, const char *value, int overwrite)
{
	char		**env_var;
	char		*tmp;
	size_t		len;

	if (overwrite)
	{
		len = ft_strlen(value) + ft_strlen(name) + 2;
		if ((env_var = getenvvar(name)))
		{
			free(*env_var);
			*env_var = ft_memalloc(len);
			tmp = ft_strendcpy(*env_var, name);
			tmp = ft_strendcpy(tmp, "=");
			tmp = ft_strendcpy(tmp, value);
		}
		else
		{
			append_environ(name, value);
		}
		return (0);
	}
	else
		return (-1);
}
