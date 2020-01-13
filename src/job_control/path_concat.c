/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_concat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:03:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/05 17:37:50 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"

int		ft_try_dirs(char **dirs, char **bin)
{
	size_t	i;
	char	*real_path;

	i = 0;
	while ((dirs[i]))
	{
		real_path = ft_strnjoin(3, dirs[i], "/", *bin);
		if (!access(real_path, F_OK))
			break ;
		ft_memdel((void**)&real_path);
		i++;
	}
	ft_tabdel(&dirs);
	ft_memdel((void**)bin);
	if (real_path)
	{
		*bin = real_path;
		return (e_success);
	}
	return (e_command_not_found);
}

int		path_concat(char **bin)
{
	char	*path;
	char	**dirs;

	if (!(path = ft_getenv("PATH")))
	{
		ft_memdel((void**)bin);
		return (e_command_not_found);
	}
	dirs = ft_strsplit(path, ":");
	return (ft_try_dirs(dirs, bin));
}
