/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:27:52 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/06 15:37:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "path.h"

char	*short_logical_path(char **cwd)
{
	int		i;

	i = 0;
	*cwd = g_pwd;
	while ((*cwd)[i])
		++i;
	if (i > 0)
		--i;
	while ((*cwd)[i] != '/')
		--i;
	++i;
	return (&(*cwd)[i]);
}

char	*short_physical_path(char **cwd)
{
	int		i;

	i = 0;
	*cwd = getcwd(NULL, 0);
	while ((*cwd)[i])
		++i;
	if (i > 0)
		--i;
	while ((*cwd)[i] != '/')
		--i;
	++i;
	return (&(*cwd)[i]);
}
