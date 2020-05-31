/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 16:24:27 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/31 16:43:53 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "input.h"
#include "libft.h"
#include "quote.h"

extern int				g_input_mode;

static int		ft_agregate_file(char **new_line)
{
	int			ret;

	if ((ret = get_next_line(STDIN_FILENO, new_line)) < 0)
		return (ERR);
	if (!(**new_line) && !ret)
	{
		ft_strdel(new_line);
		return (EOF_ERR);
	}
	return (NO_ERR);
}

static int		ft_agregate_tty(t_cursor *cursor, char **new_line)
{
	g_input_mode = 1;
	ft_init_cursor(cursor, 2);
	get_stdin(cursor, new_line);
	if (!g_input_mode)
	{
		ft_strdel(new_line);
		return (ERR);
	}
	ft_strdel(&(cursor->prompt));
	write(1, "\n", 1);
	return (NO_ERR);
}

int				ft_agregate_line(t_cursor *cursor, char **buff)
{
	int			ret;
	char		*new_line;

	if ((cursor))
	{
		if (ft_agregate_tty(cursor, &new_line) == ERR)
			return (ERR);
	}
	else if ((ret = ft_agregate_file(&new_line)) != NO_ERR)
		return (ret);
	*buff = ft_strnjoinfree(3, *buff, ft_strdup("\n"), new_line);
	return (NO_ERR);
}
