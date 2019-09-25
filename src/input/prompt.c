/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:38:55 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/07 14:36:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "libft.h"
#include "path.h"

int	g_fd_prompt;

static int	print_ifstatus(int status, char **pwd, int fd)
{
	int	ret;

	if (*g_pwd)
	{
		ret = ft_dprintf(fd,
			"\e[1m\e[38;5;14m%s \e[0m\e[38;5;160m⦗%d⦘ ➠ \e[0m",
			short_logical_path(pwd), status);
	}
	else
	{
		ret = ft_dprintf(fd,
			"\e[1m\e[38;5;14m%s \e[0m\e[38;5;160m⦗%d⦘ ➠ \e[0m",
			short_physical_path(pwd), status);
		ft_memdel((void**)pwd);
	}
	return (ret);
}

static int	print_stdprompt(char **pwd, int fd)
{
	int	ret;

	if (*g_pwd)
	{
		ret = ft_dprintf(fd, "\e[1m\e[38;5;14m%s\e[0m\e[38;5;82m ➠ \e[0m",
				short_logical_path(pwd));
	}
	else
	{
		ret = ft_dprintf(fd, "\e[1m\e[38;5;14m%s\e[0m\e[38;5;82m ➠ \e[0m",
				short_physical_path(pwd));
		ft_memdel((void**)pwd);
	}
	return (ret);
}

_Bool	prompt_display(int status)
{
	extern int	g_fd_prompt;
	int		ret;
	char	*pwd;
	
	if (!g_fd_prompt)
		return (1);
	if (status)
		ret = print_ifstatus(status, &pwd, g_fd_prompt);
	else
		ret = print_stdprompt(&pwd, g_fd_prompt);
	return (ret);
}

int	initialize_prompt_fd(void)
{
	char	*ttyname_s;
	int	fd;

	if (!isatty(STDIN_FILENO))
		return (0);
	if (!(ttyname_s = ttyname(STDIN_FILENO)))
		return (0);
	else if ((fd = open(ttyname_s, O_WRONLY)) == -1)
		return (-1);
	return (fd);
}
