/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcderror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:26:37 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/31 16:51:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin_cd.h"
#include "libft.h"
#include "error.h"

extern char		*g_progname;

int				ft_pcderror(int error_type)
{
	if (error_type == TOO_MANY_ARG)
		ft_dprintf(STDERR_FILENO, "%s: cd: Too many arguments.\n", g_progname);
	if (error_type == UNSET_HOME)
		psherror(e_home_not_set, "cd", e_builtin_type);
	else if (error_type == UNSET_OLDPWD)
		psherror(e_oldpwd_not_set, "cd", e_builtin_type);
	else if (error_type == NO_PERM)
		psherror(e_permission_denied, "cd", e_builtin_type);
	else if (error_type == NOT_DIR)
		psherror(e_not_a_directory, "cd", e_builtin_type);
	else if (error_type == TARGET_NOT_FOUND)
		psherror(e_No_such_file_or_directory, "cd", e_builtin_type);
	else if (error_type == EXCEED_LINK_LVL)
		psherror(e_too_many_levels_of_symbolic_links, "cd", e_builtin_type);
	return (1);
}
