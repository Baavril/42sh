/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_checker_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:37:29 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/08 14:24:41 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_variables.h"
#include "hash_module.h"
#include "libft.h"

extern t_htable			*g_bintable;

static int				testvarenv(char *tmp_cmp, char *argv)
{
	int			i;
	char		*key_cmp;
	extern char	**environ;

	i = 0;
	key_cmp = NULL;
	while (environ[i])
	{
		if (!(key_cmp = get_key(environ[i])))
			return (ERROR);
		if (ft_strcmp(key_cmp, tmp_cmp) == SUCCESS)
		{
			if (!(ft_strcmp("PATH", key_cmp)) && (g_bintable))
				ft_empty_htable(g_bintable);
			free(environ[i]);
			if (!(environ[i] = ft_strdup(argv)))
				return (ERROR);
			ft_strdel(&key_cmp);
			ft_strdel(&tmp_cmp);
			return (SUCCESS);
		}
		ft_strdel(&key_cmp);
		++i;
	}
	return (ERROR);
}

int				checkvarenv(char *argv)
{
	char	*tmp_cmp;

	if (!(tmp_cmp = get_key(argv)))
		return (ERROR);
	if (testvarenv(tmp_cmp, argv) == SUCCESS)
		return (SUCCESS);
	ft_strdel(&tmp_cmp);
	return (ERROR);
}
