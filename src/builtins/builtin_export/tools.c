/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by bprunev           #+#    #+#             */
/*   Updated: 2020/01/19 13:18:48 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell_variables.h"
#include "builtins.h"
#include "builtin_export.h"
#include "libft.h"

char	*get_key(char *var)
{
	int		i;
	char	*rav;

	i = 0;
	rav = NULL;
	while (var[i] && var[i] != '=')
		i++;
	if (!(rav = ft_strndup(var, i)))
		return (NULL);
	return (rav);
}

char	**realloc_environ(char **environ, char *str)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = ft_tabcpy(environ);
	ft_tabdel(&environ);
	if (!(environ = (char**)malloc(sizeof(char*) * (ft_tablen(cpy) + 2))))
		return (0);
	i = 0;
	while (cpy[i])
	{
		if (!(environ[i] = ft_strdup(cpy[i])))
			return (NULL);
		i++;
	}
	if (!(environ[i] = ft_strdup(str)))
		return (NULL);
	environ[++i] = 0;
	ft_tabdel(&cpy);
	return (environ);
}
