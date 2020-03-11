/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcderror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:26:37 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/11 12:21:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin_cd.h"
#include "libft.h"

extern char		*g_progname;

int				ft_pcderror(int error_type, char *arg)
{
	if (error_type == UNSET_HOME)
		ft_dprintf(STDERR_FILENO, "%s: cd: HOME not set.\n", g_progname);
	else if (error_type == UNSET_OLDPWD)
		ft_dprintf(STDERR_FILENO, "%s: cd: OLDPWD not set.\n", g_progname);
	else if (error_type == NO_PERM)
		ft_dprintf(STDERR_FILENO, \
				"%s: cd: %s: Pemission denied.\n", g_progname, arg);
	else if (error_type == NOT_DIR)
		ft_dprintf(STDERR_FILENO, \
				"%s: cd: %s: Not a directory.\n", g_progname, arg);
	else if (error_type == TARGET_NOT_FOUND)
		ft_dprintf(STDERR_FILENO, \
				"%s: cd: %s: No such file or directory.\n", g_progname, arg);
	else if (error_type == EXCEED_LINK_LVL)
		ft_dprintf(STDERR_FILENO, \
				"%s: cd: %s: Too many levels of symbolic links.\n", \
				g_progname, arg);
	return (1);
}
