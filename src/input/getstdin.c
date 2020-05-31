/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:02:43 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/31 17:07:50 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include "builtins.h"
#include <unistd.h>

extern int		g_ppid;

static size_t	ft_get_input_len(char *input)
{
	size_t	len;

	len = 0;
	if (input[len] < 0)
	{
		while (input[len] < 0)
			len++;
		return (len);
	}
	if (input[len] == '\033')
		return (ft_strlen(input));
	return (1);
}

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
	i = ft_get_input_len(input);
	ft_strncpy(buff, input, i);
	input += i;
	if (!(*input))
		input = NULL;
	return (1);
}

int				get_stdin(t_cursor *cursor, char **buff)
{
	int			ret;
	union u_tc	term;

	init_key_tab();
	g_inside_history = NULL;
	*buff = NULL;
	ft_bzero(term.buff, COUNT_KEY + 1);
	set_reader(&term, buff, cursor);
	ft_strdel(buff);
	*buff = ft_strdup("");
	while ((ret = ft_get_next_input(term.buff)) > 0)
	{
		if (!analyzer(cursor, buff, &term))
		{
			ft_strdel(&g_inside_history);
			ft_strdel(&cursor->prompt);
			return (0);
		}
	}
	if (ret == -1 && getppid() != g_ppid)
		cmd_exit(0, NULL);
	return (ret);
}
