/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_single_options5.c                     :+:      :+:    :+:   */
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
#include "../../../../include/builtin_test.h"
#include "../../../../libft/include/libft.h"
#include "../../../../include/builtins.h"

int		test_s_option_N(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0
	&& sb.st_mtime == sb.st_atime))
		return (e_success);
	return (e_failure);
}

int		test_s_option_O(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0
	&& sb.st_uid == getuid()))
		return (e_success);
	return (e_failure);
}

int		test_s_option_G(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0
	&& sb.st_gid == getgid()))
		return (e_success);
	return (e_failure);
}
