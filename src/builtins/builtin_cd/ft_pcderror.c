/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcderror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:26:37 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/11 17:44:55 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin_cd.h"
#include "libft.h"
#include "error.h"

extern char		*g_progname;

int				ft_pcderror(int error_type)
{
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
