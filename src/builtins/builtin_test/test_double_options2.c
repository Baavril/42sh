/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_double_options2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/10/18 17:29:13 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int	test_d_option_ef(char **argv, char *str)
{
	struct stat	file1;
	struct stat	file2;

	(void)str;
	if ((stat(argv[0], &file1) >= 0 && stat(argv[2], &file2) >= 0)
	&& file1.st_ino == file2.st_ino)
		return (e_success);
	return (e_error);
}

int	test_d_option_ot(char **argv, char *str)
{
	struct stat	file1;
	struct stat	file2;

	(void)str;
	if ((stat(argv[0], &file1) >= 0 && stat(argv[2], &file2) >= 0)
	&& file1.st_mtime < file2.st_mtime)
		return (e_success);
	return (e_error);
}

int	test_d_option_nt(char **argv, char *str)
{
	struct stat	file1;
	struct stat	file2;

	(void)str;
	if ((stat(argv[0], &file1) >= 0 && stat(argv[2], &file2) >= 0)
	&& file1.st_mtime > file2.st_mtime)
		return (e_success);
	return (e_error);
}
