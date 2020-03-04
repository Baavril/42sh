/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_single_options4.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2019/10/18 17:29:13 by bprunev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		test_s_option_x(char **argv)
{
	if (access(argv[1], X_OK) == E_SUCCESS)
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_w(char **argv)
{
	if (access(argv[1], W_OK) == E_SUCCESS)
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_v(char **argv)
{
	if (getenv(argv[1]))
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_u(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && (sb.st_mode & UID)))
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_t(char **argv)
{
	if (argv[1])
		if (isatty(atoi(argv[1])))
			return (E_SUCCESS);
	return (E_FAILURE);
}
