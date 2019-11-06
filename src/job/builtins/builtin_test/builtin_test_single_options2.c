/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_single_options2.c                     :+:      :+:    :+:   */
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

int		test_s_option_z(char **argv)
{
	if ((int)ft_strlen(argv[1]) == 0)
		return (e_success);
	return (e_failure);
}

int		test_s_option_n(char **argv)
{
	if ((int)ft_strlen(argv[1]) > 0)
		return (e_success);
	return (e_failure);
}

int		test_s_option_o(char **argv)
{
	(void)argv;
	// trouver comment getenv optnames
	return (e_failure);
}

int		test_s_option_h(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && (sb.st_mode & LINK)))
		return (e_success);
	return (e_failure);
}

int		test_s_option_g(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && (sb.st_mode & GID)))
		return (e_success);
	return (e_failure);
}
