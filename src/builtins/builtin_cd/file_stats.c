/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:39:14 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/20 18:26:57 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "builtin_cd.h"
#include "libft.h"

int				ft_get_permission(char *path)
{
	struct stat		file_stat;

	if (stat(path, &file_stat) == -1)
		return (STAT_ERROR);
	return ((file_stat.st_mode & S_IRUSR));
}

int				ft_gettype(char *path)
{
	struct stat		file_stat;

	if (lstat(path, &file_stat) == -1)
		return (STAT_ERROR);
	return (file_stat.st_mode & S_IFMT);
}

int				ft_get_targettype(char *path)
{
	struct stat		file_stat;

	if (stat(path, &file_stat) == -1)
		return (STAT_ERROR);
	return (file_stat.st_mode & S_IFMT);
}

char			*ft_get_link_target(char *link_name)
{
	char		buf[PATH_MAX];
	char		*link_target;
	ssize_t		nbytes;

	if ((nbytes = readlink(link_name, buf, PATH_MAX)) == -1)
		return (NULL);
	buf[nbytes] = '\0';
	if (!(link_target = ft_strnew(nbytes)))
		return (NULL);
	ft_memcpy(link_target, buf, nbytes + 1);
	return (link_target);
}

int				ft_is_valid_dir(char *path)
{
	struct stat		file_stat;

	if (stat(path, &file_stat) == -1)
		return (0);
	if (!(file_stat.st_mode & S_IFDIR))
		return (0);
	return ((file_stat.st_mode & S_IRUSR));
}
