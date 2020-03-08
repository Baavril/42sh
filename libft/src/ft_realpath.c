/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:47:47 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/09 20:49:43 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

char	*ft_realpath(const char *path, char *resolved_path)
{
	char	*physical;
	char	*tmp;

	if (!path)
		return (NULL);
	tmp = getcwd(NULL, 0);
	if (chdir(path))
	{
		free(tmp);
		return (NULL);
	}
	if (!(physical = getcwd(NULL, 0)))
		return (NULL);
	if (chdir(tmp))
	{
		free(tmp);
		free(physical);
		return (NULL);
	}
	free(tmp);
	if (!resolved_path)
		return (physical);
	ft_strcpy(resolved_path, physical);
	free(physical);
	return (resolved_path);
}
