/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_single_options1.c                     :+:      :+:    :+:   */
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

int		test_s_option_f(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && S_ISREG(sb.st_mode)))
		return (e_success);
	return (e_failure);
}

int		test_s_option_a(char **argv)
{
	if ((access(argv[1], F_OK) == e_success))
		return (e_success);
	return (e_failure);
}

int		test_s_option_c(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && S_ISCHR(sb.st_mode)))
		return (e_success);
	return (e_failure);
}

int		test_s_option_b(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && S_ISBLK(sb.st_mode)))
		return (e_success);
	return (e_failure);
}

int		test_s_option_d(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && S_ISDIR(sb.st_mode)))
		return (e_success);
	return (e_failure);
}
