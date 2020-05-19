/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:21:08 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/17 15:45:17 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

struct s_var	*g_svar;

int			delete_history(t_history *history)
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

static void	mv_hist(t_history **history, int max)
{
	int	len;
	int	prv;

	len = 0;
	prv = 0;
	while ((*history) && (*history)->next && prv++)
		(*history) = (*history)->next;
	while ((*history) && (*history)->previous && len++ < (max - 1) && len < prv)
		(*history) = (*history)->previous;
}

static int	write_history(t_history *history, char *home, int max)
{
	int	fd;

	mv_hist(&history, max);
	if ((fd = open(home, O_WRONLY | O_CREAT | O_APPEND, 0600)) == -1)
		return (-1);
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

int			delete(t_history *history2, int flag)
{
	int					max;
	char				*home;
	static t_history	*history = NULL;

	if (history == NULL)
		history = history2;
	if (flag == NEW_HIST)
		return (new_history(&history));
	if (assign_max_home(&max, &home) == 0)
		return (0);
	if (home[0] != '\0')
		if (write_history(history, home, max) == -1)
			ft_dprintf(2, "history: can't open %s\n", home);
	ft_strdel(&home);
	delete_history(history);
	return (1);
}
