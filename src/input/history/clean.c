/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:21:08 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 15:58:12 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

struct s_var	*g_svar;

static int	delete_history(t_history *history)
{
	t_history	*tmp;

	if (history->str)
		ft_strdel(&history->str);
	tmp = history->next;
	history = NULL;
	history = tmp;
	while (history)
	{
		if (history->str)
			ft_strdel(&history->str);
		tmp = history->next;
		free(history);
		history = NULL;
		history = tmp;
	}
	return (1);
}

static int	w_history(const char *line, int fd)
{
	int	len;

	len = ft_strlen(line);
	if (write(fd, line, len) != len)
	{
		close(fd);
		return (-1);
	}
	if (write(fd, "\n", 1) != 1)
	{
		close(fd);
		return (-1);
	}
	return (1);
}

static int	write_history(t_history *history, char *home, int max)
{
	int len;
	int fd;

	len = 0;
	if ((fd = open(home, O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
		return (-1);
	while (history && history->next)
		history = history->next;
	while (history && history->previous && len++ < (max - 1))
		history = history->previous;
	while (history && history->next)
	{
		if (w_history(history->str, fd) == -1)
			return (-1);
		history = history->next;
	}
	if (history && w_history(history->str, fd) == -1)
		return (-1);
	close(fd);
	return (1);
}

int			delete(t_history *history, char *home, int max)
{
	if (*home != '\0')
	{
		if (write_history(history, home, max) == -1)
			ft_dprintf(2, "history: can't open %s\n", home);
	}
	ft_strdel(&home);
	delete_history(history);
	return (1);
}
