/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_single_options4.c                     :+:      :+:    :+:   */
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

int		test_s_option_x(char **argv)
{
	if (access(argv[1], X_OK) == e_success)
		return (e_success);
	return (e_failure);
}

int		test_s_option_w(char **argv)
{
	if (access(argv[1], W_OK) == e_success)
		return (e_success);
	return (e_failure);
}

int		test_s_option_v(char **argv)
{
	if (getenv(argv[1]))
		return (e_success);
	return (e_failure);
}

int		test_s_option_u(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && (sb.st_mode & UID)))
		return (e_success);
	return (e_failure);
}

int		test_s_option_t(char **argv)
{
	if (argv[1])
		if (isatty(atoi(argv[1])))
			return (e_success);
	return (e_failure);
}
