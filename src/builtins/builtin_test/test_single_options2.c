/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_single_options2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/07/13 13:53:15 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		test_s_option_z(char **argv)
{
	if ((int)ft_strlen(argv[1]) == 0)
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_n(char **argv)
{
	if ((int)ft_strlen(argv[1]) > 0)
		return (E_SUCCESS);
	return (E_FAILURE);
}

/*
** Trouver comment getenv optnames
*/

int		test_s_option_o(char **argv)
{
	(void)argv;
	return (E_FAILURE);
}

int		test_s_option_h(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && (sb.st_mode & LINK)))
		return (E_SUCCESS);
	return (E_FAILURE);
}

int		test_s_option_g(char **argv)
{
	struct stat	sb;

	if ((stat(argv[1], &sb) >= 0 && (sb.st_mode & GID)))
		return (E_SUCCESS);
	return (E_FAILURE);
}
