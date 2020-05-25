/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcderror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:26:37 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/27 16:09:32 by tgouedar         ###   ########.fr       */
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
		psherror(27, "cd", e_builtin_type);
	else if (error_type == UNSET_OLDPWD)
		psherror(28, "cd", e_builtin_type);
	else if (error_type == NO_PERM)
		psherror(29, "cd", e_builtin_type);
	else if (error_type == NOT_DIR)
		psherror(30, "cd", e_builtin_type);
	else if (error_type == TARGET_NOT_FOUND)
		psherror(31, "cd", e_builtin_type);
	else if (error_type == EXCEED_LINK_LVL)
		psherror(32, "cd", e_builtin_type);
	return (1);
}
