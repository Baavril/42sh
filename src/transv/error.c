/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:56:23 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 18:56:42 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"

char	*g_progname;

const struct s_error_desc	g_errordesc[] =
{
	{ 0, "no error" },
	{ 1, "invalid input" },
	{ 1, "syntax error near unexpected token" },
	{ 1, "no such builtin" },
	{ 1, "bad substitution" },
	{ 2, "filename argument required\n.: usage: . filename [arguments]" },
	{ 2, "cannot allocate memory" },
	{ 2, "system call error" },
	{ 126, "permission denied" },
	{ 126, "is a directory" },
	{ 127, "command not found" },
	{ 127, "no such file or directory" },
	{ 128, "resource temporarily unavailable" }
};

void	psherror(int e_error, char *str, int e_message_type)
{
	if (e_message_type == e_parsing_type)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s \'%s\'\n", \
				g_progname, g_errordesc[e_error].message, str);
	}
	else if (e_message_type == e_cmd_type)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
				g_progname, str, g_errordesc[e_error].message);
	}
	else if (e_message_type == e_invalid_type)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", \
				g_progname, g_errordesc[e_error].message);
	}
}
