/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:02:43 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/01 17:08:04 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include "builtins.h"
#include <unistd.h>

extern int		g_ppid;

static int		ft_get_next_input(char buff[COUNT_KEY])
{
	size_t			i;
	static char		stock[COUNT_KEY + 1];
	static char		*input = NULL;

	ft_bzero(buff, COUNT_KEY + 1);
	if (!(input))
	{
		ft_bzero(stock, COUNT_KEY + 1);
		if (read(STDIN_FILENO, &stock, COUNT_KEY) <= 0)
			return (-1);
		input = &(stock[0]);
	}
	if (*input > 0)
		buff[0] = *(input++);
	else
	{
		i = 0;
		while (input[i] && input[i] < 0)
			i++;
		ft_strncpy(input, buff, i);
		input += i;
	}
	if (!(*input))
		input = NULL;
	return (1);
}

int				get_stdin(t_cursor *cursor, char **buff)
{
	union u_tc	term;

	if (ft_init_tab() == 1)
		return (1);
	g_inside_history = NULL;
	*buff = ft_strdup("");
	ft_bzero(term.buff, COUNT_KEY + 1);
	set_reader(&term, buff, cursor);
	while (ft_get_next_input(term.buff) > 0)
	{
		if (getppid() != g_ppid)
			cmd_exit(0, NULL);
		if (!analyzer(cursor, buff, &term))
		{
			ft_strdel(&g_inside_history);
			ft_strdel(&cursor->prompt);
			return (0);
		}
	}
	return (1);
}
