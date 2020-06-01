/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_concat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:03:13 by bprunevi          #+#    #+#             */
/*   Updated: 2020/06/01 13:17:37 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "error.h"
#include "libft.h"
#include "parser.h"

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

	if (!bin || !(*bin))
		return (e_command_not_found);
	if (**bin == '/' && !access(*bin, X_OK) && is_regfile(*bin))
		return (e_success);
	if (!(path = ft_getenv("PATH")))
	{
		ft_memdel((void**)bin);
		return (e_command_not_found);
	}
	dirs = ft_strsplit(path, ":");
	ft_strdel(&path);
	return (ft_try_dirs(dirs, bin));
}
