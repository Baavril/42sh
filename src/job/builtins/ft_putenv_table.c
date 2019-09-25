/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:49:03 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/06 15:56:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static char	**getenvvar(char **env, const char *name)
{
	int	i;
	int	j;

	if (env && name)
	{
		i = 0;
		while (env[i])
		{
			j = 0;
			while (name[j] && env[i][j] && name[j] == env[i][j])
				++j;
			if (env[i][j] != '=' || name[j])
				++i;
			else
			{
				++j;
				return (&env[i]);
			}
		}
	}
	return (NULL);
}

static void	append_environ(char ***env, const char *name, const char *value)
{
	char		**new_env;
	char		*tmp;
	int			nb;

	nb = 0;
	new_env = NULL;
	while (*env && (*env)[nb])
		++nb;
	new_env = (char**)ft_memalloc(sizeof(char**) * (nb + 2));
	--nb;
	if (*env)
		while (nb >= 0)
		{
			new_env[nb + 1] = (*env)[nb];
			--nb;
		}
	new_env[0] = (char*)ft_memalloc(ft_strlen(name) + 1 + ft_strlen(value));
	tmp = ft_strendcpy(new_env[0], name);
	tmp = ft_strendcpy(tmp, "=");
	tmp = ft_strendcpy(tmp, value);
	free(*env);
	*env = new_env;
}

int			ft_putenv_table(char ***env, const char *name, const char *value, int overwrite)
{
	char		**env_var;
	char		*tmp;
	size_t		len;

	if (overwrite)
	{
		len = ft_strlen(value) + ft_strlen(name) + 2;
		if ((env_var = getenvvar(*env, name)))
		{
			free(*env_var);
			*env_var = ft_memalloc(len);
			tmp = ft_strendcpy(*env_var, name);
			tmp = ft_strendcpy(tmp, "=");
			tmp = ft_strendcpy(tmp, value);
		}
		else
		{
			append_environ(env, name, value);
		}
		return (0);
	}
	else
		return (-1);
}
