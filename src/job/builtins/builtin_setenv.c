/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:13:47 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"

static void	print_setenv_syntax_error(char *cmd_name, char *str)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: \'%s\': not a valid identifier\n",
					g_progname, cmd_name, str);
}

static int	is_valid_chr(const char c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		 || (c >= '0' && c <= '9') || c == '_' || c == '/'))
		return (1);
	else
		return (0);
}

static int	has_invalid_syntax(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_valid_chr(str[i]))
			return (e_invalid_input);
		++i;
	}
	return (e_success);
}

int		cmd_setenv(int argc, char **argv)
{
	if (argc != 3)
	{
		psherror(e_invalid_input, argv[0], e_cmd_type);
		ft_dprintf(STDERR_FILENO, "Usage: %s VAR [VALUE]\n", argv[0]);
		return (g_errordesc[e_invalid_input].code);
	}
	if (has_invalid_syntax(argv[1]))
	{
		print_setenv_syntax_error(argv[0], argv[1]);
		return (g_errordesc[e_invalid_input].code);
	}
	else if (has_invalid_syntax(argv[2]))
	{
		print_setenv_syntax_error(argv[0], argv[2]);
		return (g_errordesc[e_invalid_input].code);
	}
	else
	{
		if ((ft_setenv(argv[1], argv[2], 1)))
			return (g_errordesc[e_cannot_allocate_memory].code);
	}
	return (e_success);
}
