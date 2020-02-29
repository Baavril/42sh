/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_single_options3.c                     :+:      :+:    :+:   */
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

int		test_s_option_s(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && sb.st_size > 0))
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_S(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && (sb.st_mode & SOCK)))
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_k(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && (sb.st_mode & STKY)))
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_r(char **argv)
{
	if (access(argv[1], R_OK) == E_SUCCESS)
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_p(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && S_ISFIFO(sb.st_mode)))
		return (E_SUCCESS);
	return (E_FAILURE);
}
