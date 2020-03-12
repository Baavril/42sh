/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:23:40 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/12 13:25:55 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>

int	is_not_a_dir(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (!S_ISDIR(path_stat.st_mode));
}

int	is_regfile(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode) || S_ISCHR(path_stat.st_mode));
}
