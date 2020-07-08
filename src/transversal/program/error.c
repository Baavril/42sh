/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:56:23 by abarthel          #+#    #+#             */
/*   Updated: 2020/07/08 18:45:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"

char						*g_progname;
extern int					g_retval;

const struct s_error_desc	g_errordesc[] =
{
	{ 0, "no error" },
	{ 1, "invalid input" },
	{ 2, "syntax error near unexpected token" },
	{ 2, "syntax error: unexpected end of file" },
	{ 1, "no such builtin" },
	{ 1, "bad substitution" },
	{ 1, "cannot assign list to array member" },
	{ 1, "not found" },
	{ 1, "ambiguous redirect" },
	{ 1, "permission denied" },
	{ 1, "is a directory" },
	{ 1, "no such file or directory" },
	{ 1, "not a valid file" },
	{ 1, "incorrect_fd" },
	{ 2, "filename argument required\n.: usage: . filename [arguments]" },
	{ 2, "cannot allocate memory" },
	{ 2, "system call error" },
	{ 127, "command not found" },
	{ 128, "resource temporarily unavailable" },
	{ 1, "division by zero" },
	{ 1, "attempted assignment to non-variable" },
	{ 1, "operand expected" },
	{ 1, "operator expected" },
	{ 1, "two argumets to unary expression" },
	{ 1, "value too great for base" },
	{ 1, "invalid variable name" },
	{ 1, "invalid number" },
	{ 1, "invalid arithmetic base" },
	{ 1, "exponent less than zero" },
	{ 1, "empty file" },
	{ 1, "history specification out of range" }
};

void	psherror(int e_error, char *str, int e_message_type)
{
	if (e_message_type == e_parsing_type)
		ft_dprintf(STDERR_FILENO, "%s: %s \'%s\'.\n", \
				g_progname, g_errordesc[e_error].message, str);
	else if (e_message_type == e_cmd_type)
		ft_dprintf(STDERR_FILENO, "%s: %s: %s.\n", \
				g_progname, str, g_errordesc[e_error].message);
	else if (e_message_type == e_invalid_type)
		ft_dprintf(STDERR_FILENO, "%s: %s.\n", \
				g_progname, g_errordesc[e_error].message);
	else if (e_message_type == e_builtin_type)
		ft_dprintf(STDERR_FILENO, "%s: %s: %s.\n", \
				g_progname, str, g_errordesc[e_error].message);
	else if (e_message_type == e_maths_type)
		ft_dprintf(STDERR_FILENO, "%s: %s: %s.\n", \
				g_progname, str, g_errordesc[e_error].message);
	g_retval = g_errordesc[e_error].code;
}
