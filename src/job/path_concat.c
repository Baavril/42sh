/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_concat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:03:13 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/25 21:48:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"

int	path_concat(char **bin)
{
	char	*beg;
	char	*env;
	char	*dir;
	char	*pathname;

	if (!(beg = ft_getenv("PATH")))
	{
		ft_memdel((void**)bin);
		return (e_command_not_found);
	}
	env = ft_strdup(beg);
	beg = env;
	while ((dir = ft_strsep(&env, ":")))
	{
		pathname = ft_strnjoin(3, dir, "/", *bin);
		if (!access(pathname, F_OK))
			break;
		ft_memdel((void**)&pathname);
	}
	ft_memdel((void**)&beg);
	ft_memdel((void**)bin);
	if (dir)
	{
		*bin = pathname;
		return (e_success);
	}
	return (e_command_not_found);
}
