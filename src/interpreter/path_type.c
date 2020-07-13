/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 01:19:32 by tgouedar          #+#    #+#             */
/*   Updated: 2020/07/10 14:16:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

int				is_regfile(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat))
		return (0);
	return (S_ISREG(path_stat.st_mode) || S_ISCHR(path_stat.st_mode));
}

int				is_dir(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat))
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}
